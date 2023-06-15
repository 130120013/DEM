#include "Vector3.h"
#include <cmath>

namespace DEM
{
	namespace utils
	{
		double vector3::magnitude()
		{
			if (x == 0 && y == 0 && z == 0)
				return 0;
			return sqrt(x * x + y * y + z * z);
		}

		vector3 vector3::normalize()
		{
			double m = magnitude();
			if (m != 0)
				return *this / m;
			else
				return *this;
		}

		vector3 vector3::operator+(vector3 other)
		{
			return vector3(x + other.x, y + other.y, z + other.z);
		}

		vector3 vector3::operator+=(vector3 other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		vector3 vector3::operator-(vector3 other)
		{
			return vector3(x - other.x, y - other.y, z - other.z);
		}

		vector3 vector3::operator-=(vector3 other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vector3 vector3::operator-()
		{
			return vector3(-x, -y, -z);
		}

		vector3 vector3::operator*=(double other)
		{
			x *= other;
			y *= other;
			z *= other;
			return *this;
		}

		double vector3::operator*(vector3 other)
		{
			return x * other.x + y * other.y + z * other.z;
		}

		vector3 vector3::operator&(vector3 other)
		{
			//|i  j  k |
			//|ax ay az|
			//|bx by bz|
			//i * ay * bz + j * az * bx + k * ax * by - k * ay * bx - j * ax * bz - i * by * az
			return vector3(y * other.z - other.y * z,
				z * other.x - x * other.z, x * other.y - y * other.x);
		}

		vector3 vector3::operator/=(double other)
		{
			x /= other;
			y /= other;
			z /= other;
			return *this;
		}

		bool vector3::operator==(vector3 other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		vector3 operator*(vector3 This, double Other)
		{
			return vector3(This.x * Other, This.y * Other, This.z * Other);
		}

		vector3 operator*(double This, vector3 Other)
		{
			return vector3(Other.x * This, Other.y * This, Other.z * This);
		}

		vector3 operator/(vector3 This, double Other)
		{
			return vector3(This.x / Other, This.y / Other, This.z / Other);
		}

		vector3 operator/(double This, vector3 Other)
		{
			return vector3(Other.x / This, Other.y / This, Other.z / This);
		}
	}
}
