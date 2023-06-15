#pragma once
#include "vector3.h"

namespace DEM
{
	class integrable
	{
	public:
		utils::vector3 F;

		virtual void integrate(double step) = 0;
	};
}
