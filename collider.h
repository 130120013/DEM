#pragma once
#include "collidable.h"
#include "box3d.h"

#ifndef NULL
#define NULL 0
#endif // !NULL


namespace DEM
{
	namespace collision
	{
		//��������� (������, ����� ������������ �������������� �����)
		template<class b_vol>
		class collider
		{
		public:
			collider() : parent(NULL), bounds(NULL), intersects(NULL)
			{}
			~collider() = default;

			collidable* parent;                                     //������, ������������ �����������
			b_vol (*bounds)(collider<b_vol>*);                      //�������������� �������������� �����
			bool (*intersects)(collider<b_vol>*, collider<b_vol>*); //�������� ����������� ���� �����������
		};
	}
}
