#include <Utils/Sphere.h>

namespace BearClaw {
	bool SphereOverlapTest(Vec3 Pos1, f32 Size1, Vec3 Pos2, f32 Size2) {
		return (Pos2 - Pos1).LengthSquared() <= (Size1 + Size2) * (Size1 + Size2);
	}
}