#pragma once
#include <vector>
#include "vector3.h"

namespace DEM
{
	namespace utils
	{
		//Грань геометрического тела
		struct face
		{
		public:
			std::vector<vector3> vertices; //Список вершин
			vector3 normal;                //Нормаль к плоскости
		};
	}
}
