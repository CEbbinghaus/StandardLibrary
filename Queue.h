#pragma once
#include "headers\Array.h"

namespace atyp {
	template<typename T>
	class Queue : private Array<T> {
		
	};

	static void test() {
		Queue<int> test;
		test.push(4);
	}
}