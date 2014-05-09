#ifndef VECTOR_THREE_H
#define VECTOR_THREE_H

#include <math.h>
#include <Utils/Math/Functions.h>
#include <stdio.h>

namespace OnionRing {
class Mat4;

class Vec3
{
public:
    float   x,y,z;

    Vec3()                          {x = 0.0f; y = 0.0f; z = 0.0f;              }
    Vec3(float n)                     {x = n; y = n; z = n;                       }
    Vec3(float x, float y, float z)       {this->x = x; this->y = y; this->z = z;     }

    Vec3& operator+=(const Vec3 &r) {x+=r.x, y+=r.y; z+=r.z; return* this;      }
    Vec3& operator-=(const Vec3 &r) {x-=r.x, y-=r.y; z-=r.z; return* this;      }
    Vec3& operator*=(float f)       {x*=f; y*=f; z*=f; return* this;            }

    void Print() const              {printf("(%.02f, %.02f, %.02f\n", x, y, z);   }

    Vec3 Cross(const Vec3 &v) const
    {
        Vec3 Ret = Vec3();
        const float x1 = y * v.z - z * v.y;
        const float y1 = z * v.x - x * v.z;
        const float z1 = x * v.y - y * v.x;
        Ret.x = x1;
        Ret.y = y1;
        Ret.z = z1;

        return Ret;
    }

    float LengthSquared() {
        return x * x + y * y + z * z;
    }

    Vec3& Normalize()
    {
        const float Length = sqrtf(x * x + y * y + z * z);

        x /= Length;
        y /= Length;
        z /= Length;

        return* this;
    }

    void Rotate(float Angle, const Vec3 &Axe);
    Vec3 Multiply(Mat4 M);
};

inline Vec3 operator+(const Vec3& l, const Vec3& r)
{
    Vec3 Ret(l.x + r.x,
             l.y + r.y,
             l.z + r.z);

    return Ret;
}

inline Vec3 operator-(const Vec3& l, const Vec3& r)
{
    Vec3 Ret(l.x - r.x,
             l.y - r.y,
             l.z - r.z);

    return Ret;
}

inline Vec3 operator*(const Vec3& l, float f)
{
    Vec3 Ret(l.x * f,
             l.y * f,
             l.z * f);

    return Ret;
}

inline bool operator>(const Vec3& l, const Vec3& r)
{
    return (l.x > r.x) && (l.y > r.y) && (l.z > r.z);
}

inline bool operator<(const Vec3& l, const Vec3& r)
{
    return (l.x < r.x) && (l.y < r.y) && (l.z < r.z);
}
}

#endif
