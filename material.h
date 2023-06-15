#pragma once
#include "clamp.h"

namespace DEM
{
	namespace physical
	{
		//Представляет упругий материал
		struct material
		{
			utils::clampMin<double, 0.> E;           //Модуль Юнга, Па
			utils::clampMinMax<double, -1., 0.5> mu; //Коэффициент Пуассона
		};
	}
}
