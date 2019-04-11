#pragma once
#include <type_traits>

namespace atyp {
	template<typename T>
	class BinaryTree {
		class Node {
			Node* l;
			Node* r;
			T* data;
		};
		
		T add(const T& a, const T& b) const
		{
			return a + b;
		}


		template<typename T>
		typename std::enable_if_t<
			std::disjunction<std::is_integer_v<T>, std::is_real_v<T>>>
		T add(const int a_int_a, const int a_int_b) const
		{
			return a_int_a + a_int_b;
		}

		//void doSomething(T * v);
		//
		//template <std::vector<int>>
		//void doSomething(std::vector<int> * v)
	};

}