#ifndef VECTOR_FOUR_H
#define VECTOR_FOUR_H

#include <System/BcTypes.h>

namespace BearClaw {
class Vec4
{
public:
    f32 x, y, z, w;
    Vec4() {x = 0.0f, y = 0.0f; z = 0.0f; w = 1.0f;}
    Vec4(f32 X, f32 Y, f32 Z, f32 W) {x = X; y = Y; z = Z; w = W;}
};
}

#endif
