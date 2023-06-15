#pragma once
#include <vector>
#include "vector3.h"

namespace DEM
{
	namespace utils
	{
		//����� ��������������� ����
		struct face
		{
		public:
			std::vector<vector3> vertices; //������ ������
			vector3 normal;                //������� � ���������
		};
	}
}
