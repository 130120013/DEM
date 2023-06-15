#pragma once
#include "clamp.h"

namespace DEM
{
	namespace environment
	{
		const float  CELSIUS_TO_KELVIN = 273.15;        //Кельвины в градусы Цельсия
		const int    STANDARD_PRESSURE = 101325;        //Стандартное атмосферное давление, Па
		const double DRY_AIR_MOLAR_MASS = 0.02896968;   //Молярная масса сухого воздуха, кг/моль
		const double WATER_VAPOR_MOLAR_MASS = 0.018016; //Молярная масса водяного пара, кг/моль
		const double UNIVERSAL_GAS_CONST = 8.31446;     //Универсальная газовая постоянная
		double step;                                    //Шаг интегрирования, с
		utils::clampMin<double, 0.> T;                  //Абсолютная температура
		utils::clampMinMax<double, 0., 1.> phi;         //Относительная влажность воздуха
		double p;                                       //Абсолютное атмосферное давление, Па
		double rho()                                    //Плотность воздуха, кг/м3
		{
			double t = T - CELSIUS_TO_KELVIN;
			double partialWaterVaporPressure =
				phi * exp((19.846 + 8.97e-03 * t + 1.248 * t * t) * t / T) * 611.26;
			return (DRY_AIR_MOLAR_MASS * (p - partialWaterVaporPressure) +
				WATER_VAPOR_MOLAR_MASS * partialWaterVaporPressure) / (UNIVERSAL_GAS_CONST * T);
		}
	}
}
