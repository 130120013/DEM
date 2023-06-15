#pragma once
#include "collider.h"

namespace DEM
{
	namespace collision
	{
		class boxCollider;
		//Функция по умолчанию для проверки пересечения двух прямоугольных параллелепипедов
		bool boxIntersection_(boxCollider* first, boxCollider* second);

		//Коллайдер, приближающий геометрию объекта прямоугольным параллелепипедом
		class boxCollider : public collider<utils::box3d>
		{
		public:
			boxCollider() : collider<utils::box3d>()
			{ intersects = (bool(*)(DEM::collision::collider<utils::box3d>*,
				DEM::collision::collider<utils::box3d>*))&boxIntersection_; }
		};
	}
}
