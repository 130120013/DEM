#define _USE_MATH_DEFINES

#include "Quaternion.h"
#include <cmath>

namespace DEM
{
	namespace utils
	{
		quaternion quaternion::operator+(quaternion& other)
		{
			return quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
		}

		quaternion quaternion::fromEulers(vector3 eulers)
		{
			eulers /= 2.;
			double cx = cos(eulers.x);
			double sx = sin(eulers.x);
			double cy = cos(eulers.y);
			double sy = sin(eulers.y);
			double cz = cos(eulers.z);
			double sz = sin(eulers.z);

			return quaternion(
				cx * cy * cz + sx * sy * sz,
				sx * cy * cz - cx * sy * sz,
				cx * sy * cz + sx * cy * sz,
				cx * cy * sz - sx * sy * cz);
		}

		vector3 quaternion::toEulers()
		{
			vector3 result;

			//x
			double sinx_cosy = 2 * (w * x + y * z);
			double cosx_cosy = 1 - 2 * (x * x + y * y);
			result.x = atan2(sinx_cosy, cosx_cosy);

			//y
			double siny = 2 * (w * y - z * x);
			if (siny >= 1)
				result.y = M_PI / 2;
			else if (siny <= -1)
				result.y = -M_PI / 2;
			else
				result.y = asin(siny);

			//z
			double sinz_cosy = 2 * (w * z + x * y);
			double cosz_cosy = 1 - 2 * (y * y + z * z);
			result.z = atan2(sinz_cosy, cosz_cosy);

			return result;
		}
	}
}
