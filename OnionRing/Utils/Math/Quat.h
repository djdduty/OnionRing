#ifndef QUAT_H
#define QUAT_H

#include <System/BcTypes.h>
#include <Utils/Math/Mat4.h>
#include <math.h>

namespace BearClaw {
class Quat
{
public:
    f32 x, y, z, w;
    Quat() {x = 0; y = 0; z = 0; w = 1;}
    Quat(f32 _x, f32 _y, f32 _z, f32 _w) {x = _x;
                                          y = _y;
                                          z = _z;
                                          w = _w;}

    void Normalize()
    {
        f32 Length = sqrtf(x * x + y * y + z * z + w * w);

        x /= Length;
        y /= Length;
        z /= Length;
        w /= Length;
    }

    Vec3 Mult(const Vec3 &v)
    {
        Vec3 Qv = Vec3(x, y, z);

        Vec3 uv = Qv.Cross(v);
        Vec3 uuv = Qv.Cross(uv);

        uv *= (w*2);
        uuv *= 2.0f;

        return Vec3(v) += uv += uuv;
    }

    Quat Mult(const Quat q)
    {

        float xx = w * q.x + x * q.w + y * q.z - z * q.y;
        float yy = w * q.y + y * q.w + z * q.x - x * q.z;
        float zz = w * q.z + z * q.w + x * q.y - y * q.x;
        float ww = w * q.w - x * q.x - y * q.y - z * q.z;

        Quat ret = Quat(xx, yy, zz, ww);

        return ret;
    }

    Quat Conjugate()
    {
        Quat ret(-x, -y, -z, w);
        return ret;
    }

    Mat4& ToMatrix()
    {
        Mat4* Ret = new Mat4();
        Ret->m[0][0] = 1 - 2 * (y * y + z * z);         Ret->m[1][0] = 2 * (x * y + w * z);                 Ret->m[2][0] = 2 * (x * z - w * y);
        Ret->m[0][1] = 2 * (x * y - w * z);             Ret->m[1][1] = 1 - 2 * (x * x + z * z);             Ret->m[2][1] = 2 * (y * z + w * x);
        Ret->m[0][2] = 2 * (x * z + w * y);             Ret->m[1][2] = 2 * (y * z - w * x);                 Ret->m[2][2] = 1 - (2 * x * x + y * y);
        Ret->m[0][3] = Ret->m[1][3] = Ret->m[2][3] =    Ret->m[3][0] = Ret->m[3][1] = Ret->m[3][2] = 0.0;   Ret->m[3][3] = 1.0;
        return *Ret;
    }
};
}

#endif
