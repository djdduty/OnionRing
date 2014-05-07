#include <Utils/Math/Functions.h>
#include <Utils/Math/Vec3.h>
#include <Utils/Math/Quat.h>
#include <Utils/Math/Mat4.h>

namespace BearClaw {
/*
 * Mat4
 */

Mat4 ScaleTransform(Vec3 Scale)
{
    Mat4 Ret = Mat4();

    Ret.m[0][0] = Scale.x;
    Ret.m[1][1] = Scale.y;
    Ret.m[2][2] = Scale.z;

    return Ret;
}

Mat4 RotateTransform(Vec3 Rot)
{
    Mat4 rx, ry, rz;

    const f32 x = ToRadian(Rot.x);
    const f32 y = ToRadian(Rot.y);
    const f32 z = ToRadian(Rot.z);

    rx.m[0][0] = 1.0f   ; rx.m[1][0] = 0.0f     ; rx.m[2][0] = 0.0f     ; rx.m[3][0] = 0.0f;
    rx.m[0][1] = 0.0f   ; rx.m[1][1] = cosf(x)  ; rx.m[2][1] = -sinf(x) ; rx.m[3][1] = 0.0f;
    rx.m[0][2] = 0.0f   ; rx.m[1][2] = sinf(x)  ; rx.m[2][2] = cosf(x)  ; rx.m[3][2] = 0.0f;
    rx.m[0][3] = 0.0f   ; rx.m[1][3] = 0.0f     ; rx.m[2][3] = 0.0f     ; rx.m[3][3] = 1.0f;

    ry.m[0][0] = cosf(y); ry.m[1][0] = 0.0f     ; ry.m[2][0] = sinf(y)  ; ry.m[3][0] = 0.0f;
    ry.m[0][1] = 0.0f   ; ry.m[1][1] = 1.0f     ; ry.m[2][1] = 0.0f     ; ry.m[3][1] = 0.0f;
    ry.m[0][2] =-sinf(y); ry.m[1][2] = 0.0f     ; ry.m[2][2] = cosf(y)  ; ry.m[3][2] = 0.0f;
    ry.m[0][3] = 0.0f   ; ry.m[1][3] = 0.0f     ; ry.m[2][3] = 0.0f     ; ry.m[3][3] = 1.0f;

    rz.m[0][0] = cosf(z); rz.m[1][0] = -sinf(z) ; rz.m[2][0] = 0.0f     ; rz.m[3][0] = 0.0f;
    rz.m[0][1] = sinf(z); rz.m[1][1] = cosf(z)  ; rz.m[2][1] = 0.0f     ; rz.m[3][1] = 0.0f;
    rz.m[0][2] = 0.0f   ; rz.m[1][2] = 0.0f     ; rz.m[2][2] = 1.0f     ; rz.m[3][2] = 0.0f;
    rz.m[0][3] = 0.0f   ; rz.m[1][3] = 0.0f     ; rz.m[2][3] = 0.0f     ; rz.m[3][3] = 1.0f;

    return rz * ry * rx;
}

Mat4 TranslationTransform(Vec3 Trans)
{
    Mat4 Ret = Mat4();

    Ret.m[3][0] = Trans.x;
    Ret.m[3][1] = Trans.y;
    Ret.m[3][2] = Trans.z;

    return Ret;
}

Mat4 LookAt(Vec3 Position, Vec3 Target, Vec3 Up)
{
    Mat4 Ret = Mat4(1.0f);
    Vec3 N = Target;
    N.Normalize();
    Vec3 U = Up;
    U.Normalize();
    U = U.Cross(N);
    Vec3 V = N.Cross(U);

    Ret.m[0][0] = U.x;   Ret.m[1][0] = U.y;   Ret.m[2][0] = U.z;   Ret.m[3][0] = Position.x;
    Ret.m[0][1] = V.x;   Ret.m[1][1] = V.y;   Ret.m[2][1] = V.z;   Ret.m[3][1] = Position.y;
    Ret.m[0][2] = N.x;   Ret.m[1][2] = N.y;   Ret.m[2][2] = N.z;   Ret.m[3][2] = Position.z;
    Ret.m[0][3] = 0.0f;  Ret.m[1][3] = 0.0f;  Ret.m[2][3] = 0.0f;  Ret.m[3][3] = 1.0f;

    return Ret;
}

Mat4 PerspectiveProjection(f32 Fov, f32 Width, f32 Height, f32 zNear, f32 zFar)
{
    Mat4 Ret = Mat4(1.0f);

    const f32 ar         = Width / Height;
    const f32 zRange     = zNear - zFar;
    const f32 tanHalfFOV = tanf(ToRadian(Fov / 2.0f));

    Ret.m[0][0] = (1.0f/tanHalfFOV) / ar; Ret.m[1][0] = 0.0f;            Ret.m[2][0] = 0.0f;                    Ret.m[3][0] = 0.0f;
    Ret.m[0][1] = 0.0f;                   Ret.m[1][1] = 1.0f/tanHalfFOV; Ret.m[2][1] = 0.0f;                    Ret.m[3][1] = 0.0f;
    Ret.m[0][2] = 0.0f;                   Ret.m[1][2] = 0.0f;            Ret.m[2][2] = (zNear + zFar)/zRange ;  Ret.m[3][2] = 2.0f * zFar*zNear/zRange;
    Ret.m[0][3] = 0.0f;                   Ret.m[1][3] = 0.0f;            Ret.m[2][3] = -1.0f;                    Ret.m[3][3] = 0.0f;

    return Ret;
}

Mat4 OrthoProjection(f32 l, f32 r, f32 t, f32 b, f32 n, f32 f) {

	Mat4 Ret = Mat4();
	Ret.m[0][0] = 2 / (r - l);				Ret.m[1][0] = 0.0f;				Ret.m[2][0] = 0.0f;					Ret.m[3][0] = -(r + l) / (r - l);
	Ret.m[0][1] = 0.0f;						Ret.m[1][1] = 2 / (t - b);		Ret.m[2][1] = 0.0f;					Ret.m[3][1] = -(t + b) / (t - b);
	Ret.m[0][2] = 0.0f;						Ret.m[1][2] = 0.0f;				Ret.m[2][2] = -2 / (f - n);			Ret.m[3][2] = -(f + n) / (f - n);
	Ret.m[0][3] = 0.0f;						Ret.m[1][3] = 0.0f;				Ret.m[2][3] = 0.0f;                 Ret.m[3][3] = 1.0f;
	
	return Ret;
}

Mat4 Transpose(Mat4 In)
{
    Mat4 Ret;
    Ret = Mat4();
    for(i32 i = 0; i < 4; i++)
    {
        for(i32 j = 0; j < 4; j++)
        {
            Ret.m[i][j] = In.m[j][i];
        }
    }

    return Ret;
}

Mat4 Inverse(Mat4 In)
{
    f64 inv[16], m[16], det;
    Mat4 Ret;

    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++)
    {
        m[j+(i*4)] = In.m[i][j];
    }

    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return nullptr;

    det = 1.0 / det;

    f64 invOut[16];
    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++)
    {
        Ret.m[i][j] = invOut[(i*4)+j];
    }

    return Ret;
}
/*
 * Quat
 */
Quat operator*(const Quat &l, const Quat &r)
{
    const f32 w = (l.w * r.w) - (l.x * r.x) - (l.y * r.y) - (l.z * r.z);
    const f32 x = (l.x * r.w) + (l.w * r.x) + (l.y * r.z) - (l.z * r.y);
    const f32 y = (l.y * r.w) + (l.w * r.y) + (l.z * r.x) - (l.x * r.z);
    const f32 z = (l.z * r.w) + (l.w * r.z) + (l.x * r.y) - (l.y * r.x);

    Quat ret(x, y, z, w);

    return ret;
}

Quat operator*(const Quat& q, Vec3 &v)
{
    const float _w = - (q.x * v.x) - (q.y * v.y) - (q.z * v.z);
    const float _x =   (q.w * v.x) + (q.y * v.z) - (q.z * v.y);
    const float _y =   (q.w * v.y) + (q.z * v.x) - (q.x * v.z);
    const float _z =   (q.w * v.z) + (q.x * v.y) - (q.y * v.x);

    Quat ret(_x, _y, _z, _w);

    return ret;
}

/*
 * Vec3 - Quat and Vec3 needing eachother forced me to move this here... :(
 */
void Vec3::Rotate(float Angle, const Vec3 &Axe)
{
    const f32 SinHalfAngle = sinf(ToRadian(Angle/2));
    const f32 CosHalfAngle = cosf(ToRadian(Angle/2));

    const f32 Rx = Axe.x * SinHalfAngle;
    const f32 Ry = Axe.y * SinHalfAngle;
    const f32 Rz = Axe.z * SinHalfAngle;
    const f32 Rw = CosHalfAngle;
    Quat RotationQ(Rx, Ry, Rz, Rw);

    Quat ConjugateQ = RotationQ.Conjugate();
    //  ConjugateQ.Normalize();
    Quat W = RotationQ * (*this) * ConjugateQ;

    x = W.x;
    y = W.y;
    z = W.z;
}

Vec3 Vec3::Multiply(Mat4 M)
{
    Vec3 Ret;

    Ret.x = M.m[0][0] * x + M.m[0][1] * y + M.m[0][2] * z;
    Ret.y = M.m[1][0] * x + M.m[1][1] * y + M.m[1][2] * z;
    Ret.z = M.m[2][0] * x + M.m[2][1] * y + M.m[2][2] * z;

    return Ret;
}
/*
 * Useful
 */

f32 ToDegree(f32 Rad)
{
    return Rad * (180/PI);
}

f32 ToRadian(f32 Angle)
{
    return Angle * (PI/180);
}
}
