#include <Rendering/Raytracer.h>

namespace OnionRing {
float mixStuff(const float &a, const float &b, const float &mx)
{
    return b * mx + a * (float(1) - mx);
}

Vec3 TraceRay(Vec3 rayorig, Vec3 raydir, std::vector<Sphere*> &spheres, int depth)
{
    float tnear = INFINITY;
    Sphere *sphere = NULL;
    for (unsigned i = 0; i < spheres.size(); ++i) {
        float t0 = INFINITY, t1 = INFINITY;
        if (spheres[i]->intersect(rayorig, raydir, &t0, &t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < tnear) {
                tnear = t0;
                sphere = spheres[i];
            }
        }
    }
    if (!sphere) return Vec3(0,0,0);//No need to go anymore

    Vec3 surfaceColor = sphere->surfaceColor;

    //TODO: all the fancy shit!

    return surfaceColor + sphere->emissionColor;

    Vec3 phit = rayorig + raydir * tnear; // point of intersection
    Vec3 nhit = phit - sphere->center; // normal at the intersection point
    nhit.Normalize(); // normalize normal direction}
}
}
