#ifndef SPHERE_H
#define SPHERE_H

#include <Utils/Math/Vec3.h>

namespace BearClaw {
	bool SphereOverlapTest(Vec3 Pos1, f32 Size1, Vec3 Pos2, f32 Size2);
}

#endif