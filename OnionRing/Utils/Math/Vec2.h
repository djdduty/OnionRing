#ifndef VECTOR_TWO_H
#define VECTOR_TWO_H

namespace OnionRing {
class Vec2
{
public:
    float x, y;
    Vec2(float v) {x = v; y = v;}
    Vec2() {x = 0.0f, y = 0.0f;}
    Vec2(float X, float Y) {x = X; y = Y;}
};

inline bool operator!=(const Vec2& l, const Vec2& r)
{
    if(l.x != r.x || l.y != l.y)
        return true;

    return false;
}
}

#endif
