#pragma once

namespace DEM
{
	namespace utils
	{
		//���������� ���� T, ������������ ����� ��������� min � ������ ��������� max
		template<class T, T min, T max>
		class clampMinMax
		{
		public:
			clampMinMax()
			{ _value = min; }

			void operator=(T value)
			{ _value = (value > min ? (value < max ? value : max) : min); }
			operator T() const
			{ return _value; }
		private:
			T _value;
		};

		//���������� ���� T, ������������ ����� ��������� min
		template<class T, T min>
		class clampMin
		{
		public:
			clampMin()
			{ _value = min; }

			void operator=(T value)
			{ _value = (value > min ? value : min); }
			operator T() const
			{ return _value; }
		private:
			T _value;
		};

		//���������� ���� T, ������������ ������ ��������� max
		template<class T, T max>
		class clampMax
		{
		public:
			clampMax()
			{ _value = T(); }

			void operator=(T value)
			{ _value = (value < max ? value : max); }
			operator T() const
			{ return _value; }
		private:
			T _value;
		};
	}
}
