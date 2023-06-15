#pragma once
#include "vector3.h"

namespace DEM
{
	namespace utils
	{
		struct box3d
		{
			vector3 center;
			vector3 halfDim;
		};
	}
}
