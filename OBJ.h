#pragma once
#include "face.h"
#include <string>

namespace DEM
{
	namespace utils
	{
		//������������ ����� ��� �������� � ������ 3D-������
		class OBJ
		{
		public:
			OBJ() : faces(NULL), _size(0)
			{}
			~OBJ()
			{ if (faces) delete[] faces; }

			face* faces; //������ ������ �������

			static OBJ* fromFile(std::string filename);
			unsigned size();
		private:
			unsigned _size;
		};
	}
}
