#pragma once
#include "collider.h"

namespace DEM
{
	namespace collision
	{
		class boxCollider;
		//������� �� ��������� ��� �������� ����������� ���� ������������� ����������������
		bool boxIntersection_(boxCollider* first, boxCollider* second);

		//���������, ������������ ��������� ������� ������������� ����������������
		class boxCollider : public collider<utils::box3d>
		{
		public:
			boxCollider() : collider<utils::box3d>()
			{ intersects = (bool(*)(DEM::collision::collider<utils::box3d>*,
				DEM::collision::collider<utils::box3d>*))&boxIntersection_; }
		};
	}
}
