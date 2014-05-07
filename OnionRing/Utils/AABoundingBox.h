#ifndef AABOUNDINGBOX_H
#define AABOUNDINGBOX_H

//#define DEBUG_DRAW_ENABLED

#include <stdlib.h>
#include <Utils/Math/Vec3.h>
#include <Resource/Mesh.h>
#include <System/BcTypes.h>
#include <Renderer/Material.h>

namespace BearClaw {
class AABoundingBox {
public:
	Vec3 HalfDim;
	Vec3 Origin;

	AABoundingBox() : HalfDim(Vec3()), Origin(Vec3()), m_VboSet(false) {}

	AABoundingBox(Vec3 Min, Vec3 Max, Vec3 Pos) : m_VboSet(false)
	{
        HalfDim = Vec3(fabs(Max.x - Min.x) / 2, fabs(Max.y - Min.y) / 2, fabs(Max.z - Min.z) / 2);
		Origin = (Max - HalfDim) -= Pos;

        #ifdef DEBUG_DRAW_ENABLED
            SetupVBO();
        #endif
	}

    AABoundingBox(Vec3 Position, VertexList Verts) : Origin(Position), m_VboSet(false)
	{
		float MaxX, MaxY, MaxZ, MinX, MinY, MinZ;
		MaxX = MaxY = MaxZ = MinX = MinY = MinZ = 0;
		for (i32 i = 0; i < Verts.size(); i++) {
			Vec3 Pos = Verts[i].Pos;
			if (Pos.x > MaxX) MaxX = Pos.x;
			if (Pos.y > MaxY) MaxY = Pos.y;
			if (Pos.z > MaxZ) MaxZ = Pos.z;

			if (Pos.x < MinX) MinX = Pos.x;
			if (Pos.y < MinY) MinY = Pos.y;
			if (Pos.z < MinZ) MinZ = Pos.z;
		}

        HalfDim = Vec3(fabs(MaxX - MinX) / 2, fabs(MaxX - MinX) / 2, fabs(MaxX - MinX) / 2);
        #ifdef DEBUG_DRAW_ENABLED
            SetupVBO();
        #endif
	}

    AABoundingBox(Vec3 Position, Vec3 HalfDimensions) : Origin(Position), HalfDim(HalfDimensions), m_VboSet(false) {
        #ifdef DEBUG_DRAW_ENABLED
            SetupVBO();
        #endif
	}

	~AABoundingBox() {
		if (m_VboSet) {
			delete m_Material;
			delete m_Mesh;
		}
	}

	bool Contains(const AABoundingBox &Other) 
	{
		Vec3 OMin = Other.Origin - Other.HalfDim;
		Vec3 OMax = Other.Origin + Other.HalfDim;
		Vec3 Max = GetMax();
		Vec3 Min = GetMin();
		if ((OMin.x < Min.x) || (OMin.y < Min.y) || (OMin.z < Min.z)) return false;
		if ((OMax.x > Max.x) || (OMax.y > Max.y) || (OMax.z > Max.z)) return false;
		return true;
	}

	bool Contains(AABoundingBox* Other)
	{
		Vec3 OMin = Other->Origin - Other->HalfDim;
		Vec3 OMax = Other->Origin + Other->HalfDim;
		Vec3 Max = GetMax();
		Vec3 Min = GetMin();
		if ((OMin.x < Min.x) || (OMin.y < Min.y) || (OMin.z < Min.z)) return false;
		if ((OMax.x > Max.x) || (OMax.y > Max.y) || (OMax.z > Max.z)) return false;
		return true;
	}

	bool Intersects(const AABoundingBox &Other)
	{
        if (fabs(Origin.x - Other.Origin.x) >= (HalfDim.x + Other.HalfDim.x)) return false;
        if (fabs(Origin.y - Other.Origin.y) >= (HalfDim.y + Other.HalfDim.y)) return false;
        if (fabs(Origin.z - Other.Origin.z) >= (HalfDim.z + Other.HalfDim.z)) return false;

		return true;
	}

	bool Intersects(AABoundingBox* Other)
	{
        if (fabs(Origin.x - Other->Origin.x) >= (HalfDim.x + Other->HalfDim.x)) return false;
        if (fabs(Origin.y - Other->Origin.y) >= (HalfDim.y + Other->HalfDim.y)) return false;
        if (fabs(Origin.z - Other->Origin.z) >= (HalfDim.z + Other->HalfDim.z)) return false;

		return true;
	}

	void Draw() 
	{
        #ifdef DEBUG_DRAW_ENABLED
		if (m_VboSet) {
			Mat4 t = Mat4(Origin);
			m_Material->Bind();
			m_Material->PrepareForRender(t);
			m_Mesh->Render();
			m_Material->UnBind();
		}
        #endif
	}

	Material* m_Material;
    bool m_VboSet = false;
private:
    Mesh* m_Mesh;

	Vec3 GetMin() { return Origin - HalfDim; }
	Vec3 GetMax() { return Origin + HalfDim; }

protected:
	void SetupVBO() 
	{
        #ifdef DEBUG_DRAW_ENABLED
		m_Material = new Material();
		m_Mesh = new Mesh();

		Vec3 Verts[8];
		Verts[0] = Vec3(HalfDim.x, HalfDim.y, HalfDim.z);
		Verts[1] = Vec3(-HalfDim.x, HalfDim.y, HalfDim.z);
		Verts[2] = Vec3(-HalfDim.x, HalfDim.y, -HalfDim.z);
		Verts[3] = Vec3(HalfDim.x, HalfDim.y, -HalfDim.z);

		Verts[4] = Vec3(HalfDim.x, -HalfDim.y, HalfDim.z);
		Verts[5] = Vec3(-HalfDim.x, -HalfDim.y, HalfDim.z);
		Verts[6] = Vec3(-HalfDim.x, -HalfDim.y, -HalfDim.z);
		Verts[7] = Vec3(HalfDim.x, -HalfDim.y, -HalfDim.z);

		VertexList VertsList = VertexList();
		VertsList.push_back(Vertex(Verts[0], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[1], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[2], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[3], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[4], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[5], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[6], Vec3(), Vec2()));
		VertsList.push_back(Vertex(Verts[7], Vec3(), Vec2()));

		IndexList Indices = IndexList();
		Indices.push_back(0); Indices.push_back(1);
		Indices.push_back(1); Indices.push_back(2);
		Indices.push_back(2); Indices.push_back(3);
		Indices.push_back(3); Indices.push_back(0);

		Indices.push_back(4); Indices.push_back(5);
		Indices.push_back(5); Indices.push_back(6);
		Indices.push_back(6); Indices.push_back(7);
		Indices.push_back(7); Indices.push_back(4);

		Indices.push_back(0); Indices.push_back(4);
		Indices.push_back(1); Indices.push_back(5);
		Indices.push_back(2); Indices.push_back(6);
		Indices.push_back(3); Indices.push_back(7);

		m_Mesh->LoadMesh(VertsList, Indices);
		m_Mesh->SetDebug(true);
        m_VboSet = true;
        #endif
	}
};
}

#endif
