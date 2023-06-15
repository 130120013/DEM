#pragma once
#include "face.h"
#include <string>

namespace DEM
{
	namespace utils
	{
		//Представляет класс для загрузки в память 3D-модели
		class OBJ
		{
		public:
			OBJ() : faces(NULL), _size(0)
			{}
			~OBJ()
			{ if (faces) delete[] faces; }

			face* faces; //Массив граней объекта

			static OBJ* fromFile(std::string filename);
			unsigned size();
		private:
			unsigned _size;
		};
	}
}
