#pragma once

#include<iostream>
#include <functional>
#include <assert.h> 
#include <cstdarg>
#include <assert.h>
#include "Assert.h"

//class String;

/*
	unshift			pushFront( value ) –add a new value to the front of the list
	push			pushBack( value ) –add a new value to the end of the list
	insert			insert( index, value ) –add a new value one-past the specified index location
	first			first() –return the first element by value
	last 			last() –return the last element by value
	size			count() –return how many elements exist in the list
	removeIndex		erase( index ) –remove an element by its index
	remove			remove( value ) –remove all elements with matching value
	pop				popBack() –remove the last element
	shift			popFront() –remove the first element
	isEmpty			empty() –return a Boolean, true if the list is empty, false otherwise
	clear			clear() –remove all elements from the list
*/


namespace atyp {

	//Array<T>
	//Dynamic Array of type T
	//Example:
	//		Array<int> values(100);
	//		values.map([](int item, int index){return pow(5, index);});
	//		//	Result should be every power of 5 from 1 to 100
	template <typename T>
	class Array
	{
		T* adr = nullptr;
		int m_size;
		T nullobj = 0;

	protected:
		//Ensures there is always memory to write to. Allocates More memory if Nessecary
		void increase(int amount = 1) {
			//Assert(m_size >= length, "TESTING")
			if ((length + amount) > m_size) {
				m_size = (m_size + amount) * 2;
				T* tmp = (T*)malloc(sizeof(T) * m_size);
				if (!tmp)throw "Out of Memory";
				memcpy(tmp, adr, sizeof(T) * length);
				if (adr != nullptr)delete[] adr;
				adr = tmp;
			}
		}

		//Ensures that the Array is Able to Decrease size
		void decrease(int amount = 1) {
			//Assert(m_size >= 0, "TESTING")
			length -= amount;
		}

		//Shifts all Array elements Up to make space for more
		void moveUp(int begin, int amount = 1) {
			increase(amount);
			memmove(adr + (begin + amount), adr + begin, sizeof(T) * (length - begin));
		}

		//Shifts all Elements down to compress the array
		void moveDown(int begin, int amount = 1) {
			decrease(amount);
			memcpy(adr + begin, adr + begin + amount, sizeof(T) * length);
		}

		// Array<T>::Iterator<T>
		//		Iterator to loop Through Array.
		class Iterator {
		public:
			T& current;
			int index;
			Iterator(T* ptr) : current(*ptr) { index = 0; };
			Iterator& operator++() {
				index++;
				
				unsigned int adress = (unsigned int)(void*)(&current + 1);
				memcpy(this, &adress, sizeof(adress));
			
				return *this; }
			//Iterator& operator++(int) { index++; current = current + 1; return *this; }
			bool operator!=(const Iterator& other) const { return other.current != current; }
			bool operator==(const Iterator& other) const { return other.current == current; }
			Iterator& operator*() { return *this; }
			operator T&() {
				return current;
			}
		};
	public:

		//length of the Array. Can be Decreased to Shorten an array
		int length;

		//	Array<T>()
		//		Default Constructor with no Data
		Array() {
			length = 0;
			m_size = 1;
			adr = (T*)malloc(sizeof(T));
		}

		//	Array<T>(int Size)
		//		Creates a empty Array of a certain Size
		Array(int size) {
			m_size = size;
			length = 0;
			adr = (T*)malloc(sizeof(T) * size);
		}

		//	Array<T>(std::initializer_list<T> values)
		//		Creates Array 
		Array(std::initializer_list<T> values) {
			m_size = length = values.size();
			adr = (T*)malloc(sizeof(T) * length);
			memcpy(adr, values.begin(), sizeof(T) * length);
		}

		//	Array<T>(Array<T>& Original)
		//		Creates a copy of the Original
		Array(Array<T>& original) {
			adr = (T*)malloc(sizeof(T) * original.length);
			memcpy(adr, original.data(), sizeof(T) * original.length);
			m_size = length = original.length;
		}

		//	Array<T>(Array<T>&& Original)
		//		Creates a copy of the Original
		Array(Array<T>&& original) {
			adr = (T*)malloc(sizeof(T) * original.length);
			memcpy(adr, original.data(), sizeof(T) * original.length);
			m_size = length = original.length;
		}

		//	~Array<T>() 
		//		Deconstructs the Array
		~Array() {
			delete[] adr;
			adr = nullptr;
		}

		//	Array<T>[Int Index]
		//		Returns the Value at a certain Index of the Array
		//		WARNING: Will returns a reference to a nullptr if the length is 0. Make sure to check the adress:
		//		example: 
		//			int& a = array[0];
		//			if(&a == nullptr)//fallback 
		//
		//		Errors Will Dissapear when Compiling for Release
		T& operator[] (int i) {
			assert(i < length && length > 0 && i >= 0);
			if (i >= length)return nullobj;
			return (adr[i]);
		}

		//	Array<T> = (Array<T>& Original)
		//		Copy Operator
		Array<T>& operator =(Array<T>& original) {
			if (adr != nullptr)delete[] adr;
			length = original.length;
			adr = (T*)malloc(sizeof(T) * length);
			memcpy(adr, original.data(), sizeof(T) * length);
			return *this;
		}

		//	Array<T> = (Array<T>&& Original)
		//		RValue Copy Operator
		Array<T>& operator =(Array<T>&& original) {
			if (adr != nullptr)delete[] adr;
			adr = (T*)malloc(sizeof(T) * original.length);
			memcpy(adr, original.data(), sizeof(T) * original.length);
			m_size = length = original.length;
			return *this;
		}

		//	Array<T> = (std::initializer_list<T> Values)
		//		Sets a Array to a Initializer List.
		Array<T>& operator =(std::initializer_list<T> values) {
			if (adr != nullptr)delete[]adr;
			m_size = length = values.size();
			adr = (T*)malloc(sizeof(T) * length);
			memcpy(adr, values.begin(), sizeof(T) * length);
			return *this;
		}

		//	Array<T> == Array<T>
		//		Compares Two Arrays by comparing each individual Element.
		bool operator ==(Array<T> other) {
			if (length != other.length)return false;

			for (int i = 0; i < other.count(); ++i)
			{
				if (adr[0] != other[0])
					return false;
			}
			return true;
		}

		//	Array<T> << Array<T>
		//		Concatinates an array with another
		Array<T>& operator <<(Array<T> other) {
			push(other);
			return *this;
		}

		//	Array<T> << T Element
		//		pushes an Element onto the end of the Array
		Array<T>& operator <<(T element) {
			push(element);
			return *this;
		}

		//	T& Array<T>::first()
		//		returns the first Element in the Array
		T& first() {
			return adr[0];
		}

		//	T& Array<T>::last()
		//		returns the last Element in the Array
		T& last() {
			return adr[length - 1];
		}

		//	void Array<T>::clear()
		//		removes all elements from an array
		void clear() {
			delete[] adr;
			adr = nullptr;
			m_size = 0;
			length = 0;
		}

		// Iterator Array<T>::begin()
		//		Returns the Iterator for the first element of the Array
		//		=Used in Range based For loops=
		Iterator begin() {
			return Iterator(&adr[0]);
		}

		//	Iterator Array<T>::end()
		//		Returns the Iterator for the last element of the Array
		//		=used in Range based For loops=
		Iterator end() {
			return Iterator(&adr[length - 1]);
		}

		//	void Array<T>::empty()
		//		empties the Array by setting its length to 0.
		//		WARNING: Memory stays intact. Only use this to write over the same memory else use .clear()
		void empty() {
			length = 0;
		}

		//	bool Array<T>::isEmpty()
		//		checks if the Array is empty by measuring its length.
		//		WARNING: Doesnt check Memory only Length.
		bool isEmpty() {
			return length == 0;
		}

		//	void Array<T>::forEach(function(T Element, int Index) => void)
		//		loops over every Element of the Array and calls a function on that element
		//		Deprechiated: Use "for(T& : Array<T>)" instead
		void forEach(std::function<void(T element, int i)> func) {
			for (int i = 0; i < length; i++) {
				func(adr[i], i);
			}
		}

		//	Array<T> Array<T>::map(function(T Element, int Index) => T result)
		//		Loops over every element Creates a new Array from the Values
		Array<T> map(std::function<T(T element, int i)> func) {
			Array<T> res(length);
			for (int i = 0; i < length; i++) {
				res[i] = func(adr[i], i);
			}
			return res;
		}

		//	Array<nT> Array<T>::map(function(T Element, int Index) => nT result)
		//		Creates a new Array of type nT and fills it with a value decided by the function
		template<typename nT>
		Array<nT> map(std::function<nT(T element, int i)> func) {
			Array<nT> res(length);
			for (int i = 0; i < length; i++) {
				res[i] = func(adr[i], i);
			}
			return res;
		}

		//	Array<T> Array<T>::copy()
		//		Returns a Copy of the Array
		Array<T> copy() {
			return Array<T>(*this);
		}

		/// LEGACY_CODE
		/*clib::string join() {
			clib::string n;
			for (t& e : (*this)) {
				n.push(e);
			}
			return n;
		}*/

		//	void Array<T>::remove(T Element)
		//		Removes every Element Matching the Argument
		void remove(T element) {
			for (int i = 0; i < length; i++) {
				if (adr[i] == element) {
					moveDown(i);
				}
			}
		}
		
		//	Array<T> Array<T>::filter(function(T Element) => bool)
		//		Returns a Array of every element that matches the Given filter
		Array<T> filter(std::function<bool(T element)> func) {
			Array<T> ret;
			for (int i = 0; i < length; i++) {
				if (func(adr[i])){
					ret.push(adr[i]);
				}
			}
			return ret;
		}

		//TODO: Implement Sorting **ELEGANTLY**
		void sort(std::function<bool(T elementA, T elementB)> lessThan) {
			auto swap = [](T* a, T* b){
				T tmp = *a;
				*a = *b;
				*b = tmp;
			};
			auto partition = 
				[&](int min, int max){
					int pivot = adr[max];
					int j = min - 1;

					for (int i = min; i < max; i++) {
						if (lessThan(adr[i], pivot)) {
							j++;
							swap(&adr[j], &adr[i]);
						}
					}
					swap(&adr[j + 1], &adr[max]);
					return j + 1;
				};

			std::function<void(int min, int max)> quickSort = [&](int min, int max){
				if (min < max) {
					int pi = partition(min, max);
					quickSort(min, pi - 1);
					quickSort(pi + 1, max);
				}
			};

			quickSort(0, length - 1);
		}

		//TODO: Implement Sorting **ELEGANTLY**
		void sort(std::function<unsigned int(T element)> getValue) {
			unsigned int largest = [this, &getValue]()->unsigned int {
				unsigned int l = 0;
				for (T& e : *this){
					l = e > l ? e : l;
				}
				return l;
			}();

			//
			int size = 0;
			for(unsigned int target = 1, result = 1; result > 0;target *= 10){
				result = (int)(largest >= target);
				size += result;
			}

			// Returns the number at a certain Digit. e.g: (52463, 3) would be 2 because 2 is the fourth character 
			auto getDigit = [](unsigned int number, int digit){
				unsigned long long int exp = pow(10, digit);
				return (unsigned int)floor((number % (exp * 10)) / exp);
			};

			//counting sort
 			auto count = [&](int digit)-> void{
				unsigned int count[10] = {0,0,0,0,0,0,0,0,0,0};
				int i = 0;

				for (; i < length; i++)
					count[getDigit(getValue(adr[i]), digit)]++;

				for (i = 1; i < 10; i++)
					count[i] += count[i - 1];

				auto result = copy();
				for (i = length - 1; i >= 0; i--) {
					int countIndex = getDigit(getValue(adr[i]), digit);
					unsigned int value = count[countIndex];
					result[value - 1] = adr[i];
					count[countIndex]--;
				}
				*this = result;
			};
			for (int i = 0; i < size; i++)
				count(i);
		}

		// void Array<T>::reverse()
		//		Reverses the Order of the Array
		void reverse() {
			Array<T> copy(*this);
			for (int i = 0; i < length; i++) {
				adr[i] = copy[length - (i + 1)];
			}
		}

		// Array<T> Array<T>::slice(int Begin, int End?)
		//		Returns a subsection of an Array as another Instance
		Array<T> slice(int begin, int end = -1) {
			assert(end >= -1 && begin >= 0);
			if (end == -1 || end > length)end = length;
			assert(end > begin);
			Array<T> res(end - begin);
			memcpy(res.data(), adr + begin, sizeof(T) * (end - begin) );
			return res;
		}
		
		//	Array<T> Array<T>::cut(int Begin, int End?)
		//		Removes the Elements from the Array and returns them as a new Instance of itself
		Array<T> cut(int begin, int end = -1) {
			assert(end >= -1 && begin >= 0);
			if (end == -1 || end > length)end = length;
			assert(end > begin);
			Array<T> res(end - begin);
			memcpy(res.data(), adr + begin, sizeof(T) * (end - begin) );
			moveDown(begin, (end - begin));
			return res;
		}

		// void Array<T>::removeIndex(int Index)
		//		Removed a Array Element by its Index
		void removeIndex(int index) {
			moveDown(index);
		}

		// int Array<T>::indexOf(T Element)
		//		Returns the Index of a Element in the Array. if it couldnt find one will return -1
		int indexOf(T element) {
			for (int i = 0; i < length; i++) {
				if(adr[i] == element)return i;
			}
			return -1;
		}

		//	Array<T> Array<T>::concat(Array<T> Data)
		//		Concatinates Another Array onto the End
		Array<T>& concat(Array<T> data) {
			push(data);
			return *this;
		}


		//------------PUSH--------------------------------------------------

		// void Array<T>::push(T Element)
		//		Pushes an Element onto the Back of an Array
		void push(T element) {
			increase();
			memcpy(adr + (length), &element, sizeof(T));
			++length;
		}

		//	void Array<T>::push(std::initializer_list<T> Values)
		//		adds a initializer list of elements onto the end of the Array
		void push(std::initializer_list<T> values) {
			increase((int)values.size());
			memcpy(adr + (length), values.begin(), sizeof(T) * values.size());
			length += (int)values.size();
		}

		//	void Array<T>::push(Array<T> Values)
		//		adds another array onto the end. Does the same as .concat
		void push(Array<T> values) {
			increase(values.length);
			memcpy(adr + (length), values.adr, sizeof(T) * values.length);
			length += values.length;
		}
		//	void Array<T>::push(T...Args)
		//		Adds Multiple Arguments on the end of the Array
		template<typename ... Args>
		void push(T element, const Args&... rest) {
			push(element);
			push(rest...);
		}

		//------------INSERT------------------------------------------------ 

		// void Array<T>::insert(int Index, T Element)
		//		Inserts a Element at a given Index
		void insert(int index, T element) {
			moveUp(index);
			adr[index] = element;
			++length;
		}

		//	void Array<T>::insert(int Index, std::Initializer_List<T> Values)
		//		Inserts a Initializer List of Values into the Array at a given Index
		void insert(int index, std::initializer_list<T> values) {
			moveUp(index, values.size());
			memcpy(adr + index, values.begin(), sizeof(T) * values.size());
			length += values.size();
		}

		// void Array<T>::insert(int Index, Array<T> Values)
		//		Inserts another Array into the Array at a certain Index
		void insert(int index, Array<T> values) {
			moveUp(index, values.length);
			memcpy(adr + index, values.adr, sizeof(T) * values.length);
			length += values.length;
		}

		//	void Array<T>::insert(int Index, T... args)
		//		Inserts Multiple Arguments into the Array at a certain Index
		template<typename ... Args>
		void insert(int index, T element, const Args&... rest) {
			insert(index, element);
			insert(++index, rest...);
		}

		//------------UNSHIFT-----------------------------------------------

		// void Array<T>::unshift(T Element)
		//		Adds a Element onto the front of the Array
		void unshift(T element) {
			moveUp(0);
			adr[0] = element;
			++length;
		}

		//	void Array<T>::unshift(std::initializer_list<T> Values)
		//		Adds a Initliazer list of Element onto the front of the array
		void unshift(std::initializer_list<T> values) {
			moveUp(0, values.size());
			memcpy(adr, values.begin(), sizeof(T) * values.size());
			length += values.size();
		}
		
		//	void Array<T>::unshift(Array<T> Values)
		//		adds another Array onto the front of the Array
		void unshift(Array<T> values) {
			moveUp(0, values.length);
			memcpy(adr, values.adr, sizeof(T) * values.length);
			length += values.length;
		}

		//	void Array<T>::unshift(T...Args)
		//		Adds Multiple arguments onto the front of the Array
		template<typename ... Args>
		void unshift(T element, const Args&... rest) {
			unshift(rest...);
			unshift(element);
		}

		//------------------------------------------------------------------

		//T Array<T>::pop()
		//		Removes the Last Element of the Array and returns it
		//		WARNING: If the Array has no Elements it will throw and error and return a reference to a nullptr. CHECK THE ADRESS OF THE RETURNED OBJECT
		T pop() {
			assert(length > 0);
			if (length <= 0)return nullobj;
			decrease();
			return adr[length];
		}

		//T Array<T>::shift()
		//		Removes the first Element of the Array and returns it
		//		WARNING: If the Array has no Elements it will throw and error and return a reference to a nullptr. CHECK THE ADRESS OF THE RETURNED OBJECT
		T shift() {
			assert(length > 0);
			if (length <= 0)return nullobj;
			T r = adr[0];
			moveDown(0);
			return r;
		}

		//	T* Array<T>::data()
		//		Returns the Adress of the Array. Can be used to Memcpy or other
		T* data() {
			return adr;
		}

		//	int Array<T>::size()
		//		Returns the Length of the Array
		int size() {
			return length;
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, Array<T>& data)
	{
		unsigned int i = 0;
		for (T& e : data) {
			os << '[' << i++ << ']' << " -> " << e << std::endl;
		}
		//data.forEach([&os](T element, int index) {os << element << std::endl; });
		return os;

	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, Array<T>&& data)
	{
		Array<T>* p = &data;
		os << *p;
		return os;

	}
}