#pragma once

namespace DEM
{
	namespace utils
	{
		//ѕредставл€ет точку или вектор в пространстве.
		struct vector3
		{
		public:
			vector3() : x(0), y(0), z(0) {}
			vector3(double x, double y, double z) : x(x), y(y), z(z) {}
			vector3(double x, double y) : x(x), y(y), z(0) {}
			~vector3() = default;

			double x;
			double y;
			double z;

			double magnitude();
			vector3 normalize();

			vector3 operator+(vector3 other);
			vector3 operator+=(vector3 other);
			vector3 operator-(vector3 other);
			vector3 operator-=(vector3 other);
			vector3 operator-();
			vector3 operator*=(double other);
			double  operator*(vector3 other);
			vector3 operator&(vector3 other);
			vector3 operator/=(double other);
			bool operator==(vector3 other);
		private:
		};

		vector3 operator*(vector3 This, double Other);
		vector3 operator*(double This, vector3 Other);
		vector3 operator/(vector3 This, double Other);
		vector3 operator/(double This, vector3 Other);
	}
}
