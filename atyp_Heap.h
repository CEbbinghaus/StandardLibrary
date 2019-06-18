#pragma once
#include <functional>
#include "atyp_Array.h"

namespace atyp
{
	template<typename T>
	class Heap{
		typedef int index;

		Array<T> data;

		std::function<int(T&)> getValue;

		index getParent(index position){
			return floor((position - 1) / 2);
		}

		index getChild(index position){
			return 2 * position + 1;
		}

		virtual bool isTrue(int a, int b){
			return a > b;
		}

		bool compare(index a, index b){
			return isTrue(getValue(data[a]), getValue(data[b]));
		}

		void sort(){
			index current = 0;

			index c1 = getChild(current);
			index c2 = c1 + 1;

			if(c1 >= data.length || c2 >= data.length)return;

			index cc = compare(c1, c2) ? c1 : c2;


			while(compare(cc, current)){
				swap(data[cc], data[current]);

				current = cc;
					
				c1 = getChild(current);
				c2 = c1 + 1;

				if(c1 >= data.length || c2 >= data.length)return;
				cc = compare(c1, c2) ? c1 : c2;
			}
		}

	public:

		Heap(std::function<int(T&)> func){
			getValue = func;
		}


		T& operator [](int index){
			return data[index];
		}


		int size(){
			return data.length;
		}

		void swap(T& a, T& b){
			T c = a;
			a = b;
			b = c;
		}

		void Push(T element){
			data.push(element);

			index current = data.length - 1;
			index parent = getParent(current);

			while(compare(current, parent)){
				swap(data[current], data[parent]);
				
				current = parent;
				parent = getParent(current);
			}
		}

		T Pop(){
			T ret = data[0];
			data[0] = data.pop();
			sort();
			return ret;
		}

	};
};