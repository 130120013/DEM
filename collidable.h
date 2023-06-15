#pragma once
#include "material.h"
#include "vector3.h"

namespace DEM
{
	namespace collision
	{
		struct normPoint;
		struct collisionData;

		//Объект для точной проверки столкновения
		class collidable
		{
		public:
			physical::material mat;                            //Материал

			virtual normPoint nPoint(utils::vector3) = 0;      //Нормаль и ближайшая точка
			virtual collisionData checkCl(collidable*) = 0;    //Точная проверка столкновения
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
