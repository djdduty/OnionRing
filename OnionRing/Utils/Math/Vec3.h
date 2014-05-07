#ifndef VECTOR_THREE_H
#define VECTOR_THREE_H

#include <System/BcTypes.h>
#include <math.h>
#include <Utils/Math/Functions.h>

namespace BearClaw {
class Mat4;

class Vec3
{
public:
    f32   x,y,z;

    Vec3()                          {x = 0.0f; y = 0.0f; z = 0.0f;              }
    Vec3(f32 n)                     {x = n; y = n; z = n;                       }
    Vec3(f32 x, f32 y, f32 z)       {this->x = x; this->y = y; this->z = z;     }

    Vec3& operator+=(const Vec3 &r) {x+=r.x, y+=r.y; z+=r.z; return* this;      }
    Vec3& operator-=(const Vec3 &r) {x-=r.x, y-=r.y; z-=r.z; return* this;      }
    Vec3& operator*=(f32 f)         {x*=f; y*=f; z*=f; return* this;            }

    void Print() const              {printf("(%.02f, %.02f, %.02f\n", x, y, z);   }

    Vec3 Cross(const Vec3 &v) const
    {
        Vec3 Ret = Vec3();
        const f32 x1 = y * v.z - z * v.y;
        const f32 y1 = z * v.x - x * v.z;
        const f32 z1 = x * v.y - y * v.x;
        Ret.x = x1;
        Ret.y = y1;
        Ret.z = z1;

        return Ret;
    }

	f32 LengthSquared() {
		return x * x + y * y + z * z;
	}

    Vec3& Normalize()
    {
        const f32 Length = sqrtf(x * x + y * y + z * z);

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

inline Vec3 operator*(const Vec3& l, f32 f)
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
