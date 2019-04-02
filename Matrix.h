#pragma once
#include "Array.h"

namespace CLib {
	template<class T, unsigned ... RestD> struct array;

	template<class T, unsigned PrimaryD >
	struct array<T, PrimaryD>
	{
		typedef T type[PrimaryD];
		type data;
		T& operator[](unsigned i) { return data[i]; }

	};

	template<class T, unsigned PrimaryD, unsigned ... RestD >
	struct array<T, PrimaryD, RestD...>
	{

		typedef typename array<T, RestD...>::type OneDimensionDownArrayT;
		typedef OneDimensionDownArrayT type[PrimaryD];
		type data;
		OneDimensionDownArrayT& operator[](unsigned i) { return data[i]; }


	};
	int main()
	{
		array<int, 2, 3>::type a4 = { { 1, 2, 3}, { 1, 2, 3} };
		array<int, 2, 3> a5{ { { 1, 2, 3}, { 4, 5, 6} } };
		std::cout << a5[1][2] << std::endl;

		array<int, 3> a6{ {1, 2, 3} };
		int myArray[10] = { 1, 2, 3 };
		std::cout << a6[1] << std::endl;

		array<int, 1, 2, 3> a7{ { { { 1, 2, 3}, { 4, 5, 6 } } } };
		std::cout << a7[0][1][2] << std::endl;
	}
}