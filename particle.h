#pragma once
#include "collidable.h"
#include "integrable.h"
#include "quaternion.h"

namespace DEM
{
	namespace physical
	{
		class particle : public collision::collidable, public integrable
		{
		public:
			particle() : collision::collidable(), integrable(), m(0), R(0)
			{}
			particle(double m, double R, utils::vector3 pos, utils::quaternion rot,
				utils::vector3 linSpd, utils::vector3 angSpd) :
				collision::collidable(), integrable(), m(m), R(R),
				pos(pos), rot(rot), linSpd(linSpd), angSpd(angSpd)
			{}
			~particle() = default;

			double m;
			double R;
			utils::vector3 pos;
			utils::quaternion rot;
			utils::vector3 linSpd;
			utils::vector3 angSpd;

			collision::normPoint nPoint(utils::vector3 from) override;
			collision::collisionData checkCl(collidable* other) override;
			void integrate(double step) override;
		private:
		};
	}
}
