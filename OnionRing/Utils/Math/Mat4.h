#ifndef MATRIX_FOUR_H
#define MATRIX_FOUR_H

#include <iostream>
#include <System/BcTypes.h>
#include <Utils/Math/Vec3.h>

namespace BearClaw {
class Mat4;
Mat4 ScaleTransform(Vec3 Scale);
Mat4 RotateTransform(Vec3 Rot);
Mat4 TranslationTransform(Vec3 Trans);
Mat4 LookAt(Vec3 Position, Vec3 Target, Vec3 Up);
Mat4 PerspectiveProjection(f32 Fov, f32 Width, f32 Height, f32 Near, f32 Far);
Mat4 OrthoProjection(f32 Left, f32 Right, f32 Top, f32 Bottom, f32 Near, f32 Far);
Mat4 Transpose(Mat4 In);
Mat4 Inverse(Mat4 In);

class Mat4
{
public:
    f32 m[4][4];

    Mat4(){ClearToIdentity();}

    Mat4(Mat4* Mat)
    {
        for(i32 i = 0; i < 4; i++)
        {
            for(i32 j = 0; i < 4; i++)
            {
                m[i][j] = Mat->m[i][j];
            }
        }
    }

    Mat4(f32 I) {if(I = 1.0f) ClearToIdentity();}
	Mat4(Vec3 p) { ClearToIdentity(); Translate(p); }

    inline void ClearToIdentity()
    {
        m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f; m[3][0] = 0.0f;
        m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f; m[3][1] = 0.0f;
        m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f; m[3][2] = 0.0f;
        m[0][3] = 0.0f; m[1][3] = 0.0f; m[2][3] = 0.0f; m[3][3] = 1.0f;
    }

    inline Mat4 operator*(const Mat4& Right) const      //left to right
    {
        Mat4 Ret;

        for(i32 i = 0; i < 4; i++)
        {
            for(i32 j = 0; j < 4; j++)
            {
                Ret.m[i][j] =   m[i][0] * Right.m[0][j] +
                                m[i][1] * Right.m[1][j] +
                                m[i][2] * Right.m[2][j] +
                                m[i][3] * Right.m[3][j];
            }
        }
        return Ret;
    }

    void Scale(Vec3 Scale)
    {
        Mat4 M = Mat4(this);
        *this = *this * ScaleTransform(Scale);
    }

    void Rotate(Vec3 Rotation)
    {
        Mat4 M = Mat4(this);
        *this = *this * RotateTransform(Rotation);
    }

    void Translate(Vec3 Translation)
    {
        *this = *this * TranslationTransform(Translation);
    }
};
}

#endif
