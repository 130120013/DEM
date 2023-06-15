#pragma once
#include "clamp.h"

namespace DEM
{
	namespace environment
	{
		const float  CELSIUS_TO_KELVIN = 273.15;        //�������� � ������� �������
		const int    STANDARD_PRESSURE = 101325;        //����������� ����������� ��������, ��
		const double DRY_AIR_MOLAR_MASS = 0.02896968;   //�������� ����� ������ �������, ��/����
		const double WATER_VAPOR_MOLAR_MASS = 0.018016; //�������� ����� �������� ����, ��/����
		const double UNIVERSAL_GAS_CONST = 8.31446;     //������������� ������� ����������
		double step;                                    //��� ��������������, �
		utils::clampMin<double, 0.> T;                  //���������� �����������
		utils::clampMinMax<double, 0., 1.> phi;         //������������� ��������� �������
		double p;                                       //���������� ����������� ��������, ��
		double rho()                                    //��������� �������, ��/�3
		{
			double t = T - CELSIUS_TO_KELVIN;
			double partialWaterVaporPressure =
				phi * exp((19.846 + 8.97e-03 * t + 1.248 * t * t) * t / T) * 611.26;
			return (DRY_AIR_MOLAR_MASS * (p - partialWaterVaporPressure) +
				WATER_VAPOR_MOLAR_MASS * partialWaterVaporPressure) / (UNIVERSAL_GAS_CONST * T);
		}
	}
}
