#include "OBJ.h"
#include <fstream>

namespace DEM
{
	namespace utils
	{
		OBJ* OBJ::fromFile(std::string filename)
		{
			std::ifstream f(filename);
			if (!f.is_open())
				return NULL;

			OBJ* obj = new OBJ;
			unsigned vs = 0, fs = 0;
			while (!f.eof())
			{
				std::string temp;
				std::getline(f, temp);
				if (temp[0] == 'v' && temp[1] == ' ')
					vs++;
				else if (temp[0] == 'f')
					fs++;
			}
			vector3* vert = new vector3[vs];
			if (!fs)
			{
				f.close();
				return NULL;
			}
			obj->faces = new face[fs];
			obj->_size = fs;
			f.clear();
			f.seekg(0);
			unsigned vi = 0, fi = 0;
			while (!f.eof())
			{
				std::string temp;
				std::getline(f, temp);
				if (temp[0] == 'v' && temp[1] == ' ')
				{
					sscanf_s(temp.substr(3).c_str(), "%lf %lf %lf",
						&vert[vi].x, &vert[vi].y, &vert[vi].z);
					vi++;
				}
				else if (temp[0] == 'f')
				{
					temp = temp.substr(1);
					do
					{
						unsigned vi;
						temp = temp.erase(0, temp.find(' ') + 1);
						sscanf_s(temp.c_str(), "%d/%*d/%*d", &vi);
						obj->faces[fi].vertices.push_back(vert[vi - 1]);
					} while (temp.find(' ') != std::string::npos);
					vector3 v1 = obj->faces[fi].vertices[1] - obj->faces[fi].vertices[0];
					vector3 v2 = obj->faces[fi].vertices[2] - obj->faces[fi].vertices[1];
					obj->faces[fi].normal = (v1 & v2).normalize();
					fi++;
				}
			}

			f.close();
			delete[] vert;
			return obj;
		}

		unsigned OBJ::size()
		{
			return _size;
		}
	}
}
