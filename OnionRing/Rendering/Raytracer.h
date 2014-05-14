#ifndef TESTRAYTRACE_H
#define TESTRAYTRACE_H

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <Utils/Math.h>
#include <algorithm>

namespace OnionRing {
struct Ray
{
    Vec3 Pos;
    Vec3 Dir;
    int Bounces;
    Ray(Vec3 D) {Pos = Vec3(); Dir = D; Bounces = 0;}
    Ray(Vec3 P, Vec3 D) {Pos = P; Dir = D; Bounces = 0;}
    Ray(Vec3 P, Vec3 D, int B) {Pos = P; Dir = D; Bounces = B;}
};

class Sphere
{
public:
    Vec3 center;
    float radius, radius2;
    Vec3 surfaceColor;
    Vec3 emissionColor;
    float transparency, reflection;
    Sphere(const Vec3 &c, const float &r, const Vec3 &sc, const float &refl = 0, const float &transp = 0, const Vec3 &ec = 0) :
        center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec),
        transparency(transp), reflection(refl)
    {}
    // compute a ray-sphere intersection using the geometric solution
    bool intersect(Vec3 rayorig, Vec3 raydir, float *t0 = NULL, float *t1 = NULL) const
    {
        Vec3 l = center - rayorig;
        float tca = l.Dot(raydir);
        if (tca < 0) return false;
        float d2 = l.Dot(l) - tca * tca;
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        if (t0 != NULL && t1 != NULL) {
            *t0 = tca - thc;
            *t1 = tca + thc;
        }

        return true;
    }
};

struct LightSortObject
{
public:
    int i;
    float d;
};

bool SortLight(const LightSortObject &l1, const LightSortObject &l2);

float mixStuff(const float &a, const float &b, const float &mx);
Vec3 TraceRay(Vec3 rayorig, Vec3 raydir, std::vector<Sphere*> &spheres, int depth);
}
#endif
