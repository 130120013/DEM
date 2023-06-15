#pragma once
#include "Vector3.h"

namespace DEM
{
	namespace utils
	{
		//Представляет кватернион
		struct quaternion
		{
		public:
			quaternion() : w(0), x(0), y(0), z(0) {}
			quaternion(double w, double x, double y, double z) :
				w(w), x(x), y(y), z(z) {}
			~quaternion() = default;

			double w;
			double x;
			double y;
			double z;

			quaternion operator+(quaternion& other);

			static quaternion fromEulers(vector3);
			vector3 toEulers();
		};
	}
}
