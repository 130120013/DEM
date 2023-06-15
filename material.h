#pragma once
#include "clamp.h"

namespace DEM
{
	namespace physical
	{
		//������������ ������� ��������
		struct material
		{
			utils::clampMin<double, 0.> E;           //������ ����, ��
			utils::clampMinMax<double, -1., 0.5> mu; //����������� ��������
		};
	}
}
