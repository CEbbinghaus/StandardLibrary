#pragma once
#include "atyp_Array.h"

namespace atyp{
	template<typename T>
	class Stack{
		Array<T> stack;

		void replace(Array<T> values) {
			stack.length = 0;
			stack.push(values);
		}
	public:

		Stack(){}

		Stack(Stack<T>& original) {
			replace(original.stack);
		}

		Stack(Array<T> m_data) {
			replace(m_data);
		}
		
		Stack(Array<T>& m_data) {
			replace(m_data);
		}
		
		Stack(Array<T>&& m_data) {
			replace(m_data);
		}

		void operator =(Stack<T>& original) {
			replace(original);
		}
		
		void operator =(Stack<T>&& original) {
			replace(original);
		}

		void push(T Element) {
			stack.push(Element);
		}

		void clear() {
			stack.clear();
		}

		T pop() {
			return stack.shift();
		}

		T& peek() {
			return stack[0];
		}

		Array<T> data() {
			return stack;
		}

		int size() {
			return stack.length;
		}
	};
}