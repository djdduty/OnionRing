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
    if (!sphere) return Vec3(0);//No need to go anymore
    if(depth < 0) return sphere->surfaceColor;

    Vec3 surfaceColor = 0;

    Vec3 phit = rayorig + raydir * tnear;
    Vec3 nhit = phit - sphere->center;
    nhit.Normalize();
    float bias = 1e-4;

    //TODO: lighting
    std::vector<LightSortObject> Lights;
    for(int i = 0; i < spheres.size(); i++)
    {
        if(spheres[i]->emissionColor.x > 0 || spheres[i]->emissionColor.y > 0 || spheres[i]->emissionColor.z > 0)
        {
            //is a light!
            Sphere* light = spheres[i];
            Vec3 LightDir = light->center - phit;
            float Distance = LightDir.Length();
            LightSortObject ls;
            ls.d = Distance;
            ls.i = i;
            Lights.push_back(ls);
        }
    }

    std::sort(Lights.begin(), Lights.end(), SortLight);
    int size = Lights.size();
    if(size > 4) size = 4;

    for(int i = 0; i < size; i++)
    {
        Sphere* light = spheres[Lights[i].i];
        Vec3 LightDir = light->center - phit;
        bool blocked = false;
        LightDir.Normalize();
        float DiffuseFactor = nhit.Dot(LightDir);
        Vec3 DiffuseColor = Vec3();
        Vec3 SpecularColor = Vec3();
        Vec3 AmbientColor = Vec3(sphere->surfaceColor * 0.2);

        for(int n = 0; n < spheres.size(); n++)
        {
            if(Lights[i].i != n)
            {
                float t0, t1;
                if(spheres[n]->intersect(phit+nhit*bias, LightDir, &t0, &t1))
                {
                    blocked = true;
                }
            }
        }

        if(!blocked)
        {
            if(DiffuseFactor > 0)
            {
                DiffuseColor = light->emissionColor.Normalize() * (DiffuseFactor*1.2);
                surfaceColor += sphere->surfaceColor * DiffuseColor + SpecularColor + AmbientColor;
            }
            else
            {
                surfaceColor += AmbientColor;
            }
        }
        else
            surfaceColor += AmbientColor;
    }
    //

    bool inside = false;
    if(raydir.Dot(nhit) > 0) nhit *= -1, inside = true;

    if((sphere->transparency + 0 || sphere->reflection > 0) && depth < 2)
    {
        float facingratio = (raydir*-1).Dot(nhit);
        float fresneleffect = mixStuff(pow(1-facingratio, 3), 1, 0.1);
        Vec3 refldir = raydir - nhit * 2 * raydir.Dot(nhit);
        refldir.Normalize();
        Vec3 reflection = TraceRay(phit+nhit*bias, refldir, spheres, depth+1);
        float param1 = (1.0 - sphere->reflection);
        float param2 = sphere->reflection;
        surfaceColor.x = (param1 * surfaceColor.x + param2 * reflection.x);
        surfaceColor.y = (param1 * surfaceColor.y + param2 * reflection.y);
        surfaceColor.z = (param1 * surfaceColor.z + param2 * reflection.z);
    }

    return surfaceColor + sphere->emissionColor;
}

bool SortLight(const LightSortObject &l1, const LightSortObject &l2) {return l1.d < l2.d;}
}
