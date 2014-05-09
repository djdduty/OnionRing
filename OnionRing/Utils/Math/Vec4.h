#ifndef VECTOR_FOUR_H
#define VECTOR_FOUR_H

namespace BearClaw {
class Vec4
{
public:
    float x, y, z, w;
    Vec4() {x = 0.0f, y = 0.0f; z = 0.0f; w = 1.0f;}
    Vec4(float X, float Y, float Z, float W) {x = X; y = Y; z = Z; w = W;}
};
}

#endif
