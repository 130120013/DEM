#include "particle.h"

DEM::collision::normPoint DEM::physical::particle::nPoint(utils::vector3 from)
{
	utils::vector3 dir = (from - pos).normalize();
	return { dir, pos + dir * R };
}

DEM::collision::collisionData DEM::physical::particle::checkCl(collidable* other)
{
	collision::normPoint n_pt = other->nPoint(pos);
	return { this, other, R - (n_pt.point - pos).magnitude() };
}

void DEM::physical::particle::integrate(double step)
{

}
