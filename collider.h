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
		//Коллайдер (объект, грубо приближающий геометрическую форму)
		template<class b_vol>
		class collider
		{
		public:
			collider() : parent(NULL), bounds(NULL), intersects(NULL)
			{}
			~collider() = default;

			collidable* parent;                                     //Объект, приближаемый коллайдером
			b_vol (*bounds)(collider<b_vol>*);                      //Ограничивающая геометрическая форма
			bool (*intersects)(collider<b_vol>*, collider<b_vol>*); //Проверка пересечения двух коллайдеров
		};
	}
}
