#include "boxCollider.h"

bool DEM::collision::boxIntersection_(boxCollider* first, boxCollider* second)
{
	if (first->parent == second->parent)
		return false;
	utils::box3d a = first->bounds(first), b = second->bounds(second);
	utils::vector3 aC = a.center, aH = a.halfDim,
		bC = b.center, bH = b.halfDim;
	return
		aC.x - aH.x <= bC.x + bH.x &&
		aC.x + aH.x >= bC.x - bH.x &&
		aC.y - aH.y <= bC.y + bH.y &&
		aC.y + aH.y >= bC.y - bH.y &&
		aC.z - aH.z <= bC.z + bH.z &&
		aC.z + aH.z >= bC.z - bH.z;
}
