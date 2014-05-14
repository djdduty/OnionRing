#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define PI 3.14159265

namespace OnionRing {

float ToRadian(float Angle);
float ToDegree(float Rad);
inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

inline float clampColor(float x)
{
    return clamp(x, 0, 255);
}
}

#endif
