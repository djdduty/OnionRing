#ifndef OCTREE_H
#define OCTREE_H

#include <Utils/AABoundingBox.h>
#include <Scene/SceneNode.h>
#include <algorithm>

namespace BearClaw {
class Octree
{
private:
	Octree* m_Children[8];
	i32 m_MaxObjectsPerNode;
	i32 m_MinObjectsPerNode;
	Octree* m_Parent;
	bool m_IsLeafNode;
	bool m_HasParent;

public:
	AABoundingBox BoundingBox;
	std::vector<SceneNode*> Data;
	
    Octree(Vec3 Origin, Vec3 HalfDim, Octree* Parent = nullptr, bool HasParent = false, i32 MaxObj = 3, i32 MinObj = 1) : BoundingBox(Origin, HalfDim)
	{
		m_MaxObjectsPerNode = MaxObj;
		m_MinObjectsPerNode = MinObj;

		Data = std::vector<SceneNode*>();
		m_Parent = Parent;
		m_HasParent = HasParent;
        m_IsLeafNode = true;
	}

	~Octree() 
	{
		if (!IsLeafNode())
			for (i32 i = 0; i < 8; i++)
				delete m_Children[i];
	}

	inline i32 OctantContainingPoint(Vec3 Point) 
	{
		i32 Oct = 0;
		int oct = 0;
		if (Point.x >= BoundingBox.Origin.x) oct |= 4;
		if (Point.y >= BoundingBox.Origin.y) oct |= 2;
		if (Point.z >= BoundingBox.Origin.z) oct |= 1;
		return oct;
	}

	inline bool IsLeafNode() 
	{
		return m_IsLeafNode;
	}

	bool Insert(SceneNode* Node)
	{
        if (!BoundingBox.Contains(Node->GetAABB()) && m_HasParent)
            return false;

		if (Data.size() >= m_MaxObjectsPerNode && m_IsLeafNode) {
            Split();
		}

		if (m_IsLeafNode) {
			Data.push_back(Node);
            //BC_LOG("Node %s inserted...\n", Node->GetName().c_str());
			return true;
		}

		i32 i = OctantContainingPoint(Node->GetAABB()->Origin);
        if (m_Children[i]->Insert(Node) == false) {
			Data.push_back(Node);
            //BC_LOG("Node %s inserted...\n", Node->GetName().c_str());
        }
		return true;
	}

	void Split() 
	{
		if (m_IsLeafNode) {
			m_IsLeafNode = false;
			for (i32 i = 0; i < 8; i++) {
				Vec3 ChildOrigin = BoundingBox.Origin;
				ChildOrigin.x += BoundingBox.HalfDim.x * (i & 4 ? .5f : -.5f);
				ChildOrigin.y += BoundingBox.HalfDim.y * (i & 2 ? .5f : -.5f);
				ChildOrigin.z += BoundingBox.HalfDim.z * (i & 1 ? .5f : -.5f);
				m_Children[i] = new Octree(ChildOrigin, BoundingBox.HalfDim * 0.5, this, true);
			}

            std::vector<SceneNode*> DataCopy = std::move(Data);
			for (i32 i = 0; i < DataCopy.size(); i++) {
                Insert(DataCopy[i]);
			}
		}
	}

	void Merge()
	{
		if (!m_IsLeafNode) {
			for (i32 i = 0; i < 8; i++) {
				if (!m_Children[i]->HasZeroElements())
					return;
			}

			for (i32 i = 0; i < 8; i++) {
				delete m_Children[i];
			}
            m_IsLeafNode = true;
		}
	}

	void GetNodesNearPosition(Vec3 Pos, std::vector<SceneNode*>& Results, f32 MaxDistance = 0.0f) 
	{
		if (!m_IsLeafNode) {
			i32 Oct = OctantContainingPoint(Pos);
			m_Children[Oct]->GetNodesNearPosition(Pos, Results, MaxDistance);
		}
		for (i32 i = 0; i < Data.size(); i++) {
			Vec3 HalfDim = Data[i]->GetAABB()->HalfDim;
			f32 MaxDim = max(max(HalfDim.x, HalfDim.y), HalfDim.z);
            if ((Data[i]->GetAABB()->Origin - Pos).LengthSquared() <= (MaxDim + MaxDistance) * (MaxDim + MaxDistance))
				Results.push_back(Data[i]);
		}
	}

	void Update()
	{
        if (!m_IsLeafNode)
			for (i32 i = 0; i < 8; i++) 
				if (!m_IsLeafNode) {
					m_Children[i]->Update();
					//BC_LOG("Child node updating\n");
				}

        #ifdef DEBUG_DRAW_ENABLED
            Draw();
        #endif

		if (m_HasParent && HasZeroElements()) {
			m_Parent->Merge();
			return;
		}

		std::vector<SceneNode*> ReinsertList = std::vector<SceneNode*>();
        for (i32 i = Data.size()-1; i >= 0; --i) {
            if (Data[i]->GetModified()) {
                Data[i]->ResolveModification();
                ReinsertList.push_back(Data[i]);
                Data.erase(Data.begin() + i);
                //BC_LOG("Node %s moved...\n", Data[i]->GetName().c_str());
			}
		}

		for (i32 i = 0; i < ReinsertList.size(); i++) {
			if (!BoundingBox.Contains(ReinsertList[i]->GetAABB()))
				GetTopNode()->Insert(ReinsertList[i]);
			else
				Insert(ReinsertList[i]);
		}
	}

	Octree* GetTopNode() 
	{
		if (!m_HasParent)
			return this;

		return m_Parent->GetTopNode();
	}

	void Draw()
	{
		BoundingBox.Draw();
	}

	bool HasZeroElements() {
		bool Ret = true;
		if (m_IsLeafNode && Data.size() == 0)
			return true;
		if (m_IsLeafNode)
			return false;
		else {
			for (i32 i = 0; i < 8; i++) {
				if (!m_Children[i]->HasZeroElements())
					Ret = false;
			}
		}

		return Ret;
	}
};
}

#endif
