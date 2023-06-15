#pragma once
#include "material.h"
#include "vector3.h"

namespace DEM
{
	namespace collision
	{
		struct normPoint;
		struct collisionData;

		//������ ��� ������ �������� ������������
		class collidable
		{
		public:
			physical::material mat;                            //��������

			virtual normPoint nPoint(utils::vector3) = 0;      //������� � ��������� �����
			virtual collisionData checkCl(collidable*) = 0;    //������ �������� ������������
		private:
		};

		struct normPoint
		{
			utils::vector3 normal;
			utils::vector3 point;
		};

		struct collisionData
		{
			collidable* first;
			collidable* second;
			double overlap;
		};
	}
}
