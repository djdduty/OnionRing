#ifndef MATTHREE_H
#define MATTHREE_H

#include <Utils/Math.h>

namespace OnionRing {
class Mat3
{
public:
    float m[3][3];

    Mat3(){Zero();}

    Mat3(Mat4 M, bool NormalMatrix)
    {
        Mat4 In = M;
        if(NormalMatrix)
            In = Transpose(Inverse(M));

        for (int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                m[i][j] = In.m[i][j];
            }
        }
    }

    void Zero()
    {
        for (int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                m[i][j] = 0;
            }
        }
    }
};
}

#endif
