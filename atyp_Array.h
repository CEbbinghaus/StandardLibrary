#pragma once

#include<iostream>
#include <functional>
#include <cstdarg>
#include "atyp_Assert.h"
/*
unshift			pushFront( value ) �add a new value to the front of the list
push			pushBack( value ) �add a new value to the end of the list
insert			insert( index, value ) �add a new value one-past the specified index location
first			first() �return the first element by value
last 			last() �return the last element by value
size			count() �return how many elements exist in the list
removeIndex		erase( index ) �remove an element by its index
remove			remove( value ) �remove all elements with matching value
pop				popBack() �remove the last element
shift			popFront() �remove the first element
isEmpty			empty() �return a Boolean, true if the list is empty, false otherwise
clear			clear() �remove all elements from the list
*/

using uint = unsigned int;

//Array<T>
//Dynamic Array of type T
//Example:
//		Array<int> values(100);
//		values.map([](int item, int index){return pow(5, index);});
//		//	Result should be every power of 5 from 1 to 100
template <typename T>
class Array{
	T* adr;
	uint m_size;

private:
	//Ensures there is always memory to write to. Allocates More memory if Nessecary
	void increase(uint amount = 1){
		if((length + amount) > m_size){
			m_size = (m_size + amount) * 2;
			T* tmp = (T*)malloc(sizeof(T) * m_size);
			if(!tmp)throw "Out of Memory";
			memcpy(tmp, adr, sizeof(T) * length);
			if(adr != nullptr)free(adr);
			adr = tmp;
		}
	}

	//Ensures that the Array is Able to Decrease size
	void decrease(int amount = 1){
		if(length > 0)
			length -= amount;
	}

	//Shifts all Array elements Up to make space for more
	void moveUp(int begin, int amount = 1){
		increase(amount);
		memmove(adr + (begin + amount), adr + begin, sizeof(T) * (length - begin));
	}

	//Shifts all Elements down to compress the array
	void moveDown(uint begin, uint amount = 1){
		//assert(begin >= 0 && length >= 1);
		if(length >= 1 && begin + amount < length)
			memcpy(adr + begin, adr + begin + amount, sizeof(T) * (length - (begin + amount)));
		decrease(amount);
	}

	// Array<T>::Iterator<T>
	//		Iterator to loop Through Array.
	class Iterator{
	public:

		T* current;
		size_t index;

		Iterator(T* ptr) : current(ptr){
			index = 0;
		};
		Iterator& operator++(){
			++index;

			++current;

			return *this;
		}
		bool operator!=(const Iterator& other) const{
			return other.current != current;
		}
		Iterator& operator*(){
			return *this;
		}

		operator T&(){
			return *current;
		}
	};
public:

	//length of the Array. Can be Decreased to Shorten an array
	uint length;

	//	Array<T>()
	//		Default Constructor with no Data
	Array(){
		length = 0;
		m_size = 1;
		adr = (T*)malloc(sizeof(T));
	}

	//	Array<T>(int Size)
	//		Creates a empty Array of a certain Size
	Array(int size){
		length = m_size = size;
		adr = (T*)malloc(sizeof(T) * size);
		memset(adr, 0, sizeof(T) * size);
	}

	//	Array<T>(std::initializer_list<T> values)
	//		Creates Array 
	Array(std::initializer_list<T> values){
		m_size = length = (int)values.size();
		adr = (T*)malloc(sizeof(T) * length);
		memcpy(adr, values.begin(), sizeof(T) * length);
	}

	//	Array<T>(Array<T>& Original)
	//		Copy Constructor
	Array(const Array<T>& original){
		adr = (T*)malloc(sizeof(T) * original.length);
		memcpy(adr, original.adr, sizeof(T) * original.length);
		m_size = length = original.length;
	}

	//	Array<T>(Array<T>&& Original)
	//		Move Constructor
	Array(Array<T>&& original) noexcept{
		adr = original.adr;
		original.adr = nullptr;
		m_size = original.m_size;
		length = original.length;
	}

	//	~Array<T>() 
	//		Deconstructs the Array
	~Array(){
		if(adr != nullptr)
			free(adr);
		adr = nullptr;
	}

	//  T& Array<T>[uint Index]
	//		Returns the Value at a certain Index of the Array
	T& operator[](uint i){
		//assert(i < length && length > 0 && i >= 0);
		if(i >= length)throw "Trying to Access Data outside the Array";
		return (adr[i]);
	}

	//	T& Array<T>::get(uint index)
	//		Returns the Element at the given Index
	T& get(uint i){
		if(i >= length)throw "Trying to Access Data outside the Array";
		return (adr[i]);
	}

	//	Array<T> = (Array<T>& Original)
	//		Copy Assignment Operator
	Array<T>& operator =(const Array<T>& original){
		if(adr != nullptr)free(adr);
		m_size = length = original.length;
		adr = (T*)malloc(sizeof(T) * length);
		memcpy(adr, original.adr, sizeof(T) * length);
		return *this;
	}

	//	Array<T> = (Array<T>&& Original)
	//		RValue Assignment Operator
	Array<T>& operator =(Array<T>&& original) noexcept{
		if(adr != nullptr)free(adr);
		adr = original.adr;
		original.adr = nullptr;
		m_size = original.m_size;
		length = original.length;
		return *this;
	}

	//	Array<T> = (std::initializer_list<T> Values)
	//		Sets a Array to a Initializer List.
	Array<T>& operator =(std::initializer_list<T> values){
		if(adr != nullptr)free(adr);
		length = m_size = (int)values.size();
		adr = (T*)malloc(sizeof(T) * length);
		memcpy(adr, values.begin(), sizeof(T) * length);
		return *this;
	}

	//	Array<T> == const Array<T>&
	//		Compares Two Arrays by comparing each individual Element.
	bool operator ==(const Array<T>& other){
		if(length != other.length)return false;

		for(int i = 0; i < other.length; ++i){
			if(adr[0] != other[0])
				return false;
		}
		return true;
	}

	//	Array<T> << const Array<T>&
	//		Concatinates an array with another
	Array<T>& operator <<(const Array<T>& other){
		push(other);
		return *this;
	}

	//	Array<T> << cosnst T& Element
	//		pushes an Element onto the end of the Array
	Array<T>& operator <<(const T& element){
		push(element);
		return *this;
	}

	//	T& Array<T>::first()
	//		returns the first Element in the Array
	T& first(){
		return adr[0];
	}

	//	T& Array<T>::last()
	//		returns the last Element in the Array
	T& last(){
		return adr[length - 1];
	}

	//	void Array<T>::clear()
	//		removes all elements from an array
	void clear(){
		free(adr);
		adr = nullptr;
		m_size = 0;
		length = 0;
	}

	//	Array<T>& Array<T>::fill(const T& value)
	//		Fills the Array from start to End with the Value
	Array<T>& fill(const T& value){
		for(uint i = 0; i < length; ++i){
			adr[i] = value;
		}
		return *this;
	}

	//	Array<T>& Array<T>::fill(function() => T)
	//		Fills the Array from start to End with the Results of the Function
	Array<T>& fill(std::function<T()> func){
		for(int i = 0; i < length; ++i){
			adr[i] = func();
		}
		return *this;
	}

	//	Array<T>& Array<T>::fill(unsigned int startIndex, const T& value)
	//		Fills the Array from the StartIndex to End with copies of the value 
	Array<T>& fill(uint start, const T& value){
		for(int i = start; i < length; ++i){
			adr[i] = value;
		}
		return *this;
	}

	//	Array<T>& Array<T>::fill(unsigned int startIndex, function() => T)
	//		Fills the Array from the StartIndex to End with the Results of the Function
	Array<T>& fill(uint start, std::function<T()> func){
		for(int i = start; i < length; ++i){
			adr[i] = func();
		}
		return *this;
	}

	//	Array<T>& Array<T>::fill(unsigned int startIndex, unsigned int amount, const T& value)
	//		Fills amount elements from startIndex with Copies of the value
	Array<T>& fill(uint start, uint size, const T& value){
		for(int i = start; i < start + size; ++i){
			adr[i] = value;
		}
		return *this;
	}

	//	Array<T>& Array<T>::fill(unsigned int startIndex, unsigned int amount, function() => T)
	//		Fills amount elements from startIndex with Copies of the value
	Array<T>& fill(uint start, uint size, std::function<T()> func){
		for(int i = start; i < start + size; ++i){
			adr[i] = func();
		}
		return *this;
	}

	// Iterator Array<T>::begin()
	//		Returns the Iterator for the first element of the Array
	//		=Used in Range based For loops=
	Iterator begin(){
		if(!length)
			return Iterator(nullptr);
		return Iterator(&adr[0]);
	}

	//	Iterator Array<T>::end()
	//		Returns the Iterator for the last element of the Array
	//		=used in Range based For loops=
	Iterator end(){
		if(!length)
			return Iterator(nullptr);
		return Iterator(&adr[length]);
	}

	//	void Array<T>::empty()
	//		empties the Array by setting its length to 0.
	//		WARNING: Memory stays intact. Only use this to write over the same memory else use .clear()
	void empty(){
		length = 0;
	}

	//	bool Array<T>::isEmpty()
	//		checks if the Array is empty by measuring its length.
	//		WARNING: Doesnt check Memory only Length.
	bool isEmpty(){
		return length == 0;
	}


	//	Array<T> Array<T>::forEach(function() => void)
	//		loops over every Element of the Array and calls a function on that element
	void forEach(std::function<void()> func) {
		for (int i = 0; i < length; i++) {
			func();
		}
	}

	//	Array<T> Array<T>::forEach(function(const T& Element) => void)
	//		loops over every Element of the Array and calls a function on that element
	void forEach(std::function<void(T& element)> func) {
		for (uint i = 0; i < length; i++) {
			func(adr[i]);
		}
	}

	//	Array<T> Array<T>::forEach(function(const T& Element, int Index) => void)
	//		loops over every Element of the Array and calls a function on that element
	void forEach(std::function<void(T& element, int i)> func){
		for(int i = 0; i < length; i++){
			func(adr[i], i);
		}
	}

	//	Array<nT> Array<T>::map(function() => nT result)
	//		Creates a new Array of type nT and fills it with values returned by the function
	template<typename nT>
	Array<nT> map(std::function<nT()> func) {
		Array<nT> res(length);
		for (int i = 0; i < length; i++) {
			res[i] = func();
		}
		return res;
	}

	//	Array<nT> Array<T>::map(function(const T& Element) => nT result)
	//		Creates a new Array of type nT and fills it with values returned by the function
	template<typename nT>
	Array<nT> map(std::function<nT(const T & element)> func) {
		Array<nT> res(length);
		for (uint i = 0; i < length; i++) {
			res[i] = func(adr[i]);
		}
		return res;
	}

	//	Array<nT> Array<T>::map(function(const T& Element, int Index) => nT result)
	//		Creates a new Array of type nT and fills it with values returned by the function
	template<typename nT>
	Array<nT> map(std::function<nT(const T& element, int i)> func){
		Array<nT> res(length);
		for(int i = 0; i < length; i++){
			res[i] = func(adr[i], i);
		}
		return res;
	}


	//	Array<T> Array<T>::copy()
	//		Returns a Copy of the Array
	Array<T> copy(){
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
	void remove(T element){
		for(uint i = 0; i < length; i++){
			if(adr[i] == element){
				moveDown(i);
			}
		}
	}

	//	Array<T> Array<T>::filter(function(T Element) => bool)
	//		Returns a Array of every element that matches the Given filter
	Array<T> filter(std::function<bool(T element)> func){
		Array<T> ret;
		for(int i = 0; i < length; i++){
			if(func(adr[i])){
				ret.push(adr[i]);
			}
		}
		return ret;
	}

	//	void Array<T>::sort(function(T elementA, T elementB) => bool)
	//		Sorts an Array using QuickSort. Provide a Function that compares A to B and returns true if A is less than B.
	void sort(std::function<bool(T elementA, T elementB)> lessThan){
		auto swap = [](T* a, T* b){
			T tmp = *a;
			*a = *b;
			*b = tmp;
		};
		auto partition =
			[&](int min, int max){
			T pivot = adr[max];
			int j = min - 1;

			for(int i = min; i < max; i++){
				if(lessThan(adr[i], pivot)){
					j++;
					swap(&adr[j], &adr[i]);
				}
			}
			swap(&adr[j + 1], &adr[max]);
			return j + 1;
		};

		std::function<void(int min, int max)> quickSort = [&](int min, int max){
			if(min < max){
				int pi = partition(min, max);
				quickSort(min, pi - 1);
				quickSort(pi + 1, max);
			}
		};

		quickSort(0, length - 1);
	}

	//	void Array<T>::sort(function(T Element) => uint)
	//		Sorts an Array using Counting sort. Very efficient but requires Unigned Int's to work.
	void sort(std::function<uint(T element)> getValue){
		uint largest = [this, &getValue]()->uint{
			uint l = 0;
			for(T& e : *this){
				l = getValue(e) > l ? getValue(e) : l;
			}
			return l;
		}();

		//
		int size = 0;
		for(uint target = 1, result = 1; result > 0; target *= 10){
			result = (int)(largest >= target);
			size += result;
		}

		// Returns the number at a certain Digit. e.g: (52463, 3) would be 2 because 2 is the fourth character 
		auto getDigit = [](uint number, int digit){
			unsigned long long int exp = pow(10, digit);
			return (uint)floor((number % (exp * 10)) / exp);
		};

		//counting sort
		auto count = [&](int digit)-> void{
			uint count[10] = {0,0,0,0,0,0,0,0,0,0};
			int i = 0;

			for(; i < length; i++)
				count[getDigit(getValue(adr[i]), digit)]++;

			for(i = 1; i < 10; i++)
				count[i] += count[i - 1];

			auto result = copy();
			for(i = length - 1; i >= 0; i--){
				int countIndex = getDigit(getValue(adr[i]), digit);
				uint value = count[countIndex];
				result[value - 1] = adr[i];
				count[countIndex]--;
			}
			*this = result;
		};
		for(int i = 0; i < size; i++)
			count(i);
	}

	// void Array<T>::reverse()
	//		Reverses the Order of the Array
	void reverse(){
		Array<T> copy(*this);
		for(int i = 0; i < length; i++){
			adr[i] = copy[length - (i + 1)];
		}
	}

	// Array<T> Array<T>::slice(int Begin, int End?)
	//		Returns a subsection of an Array as another Instance
	Array<T> slice(int begin, int end = -1){
		//assert(end >= -1 && begin >= 0);
		if(end == -1 || end > length)end = length;
		//assert(end > begin);
		Array<T> res(end - begin);
		memcpy(res.adr, adr + begin, sizeof(T) * (end - begin));
		return res;
	}

	//	Array<T> Array<T>::cut(int Begin, int End?)
	//		Removes the Elements from the Array and returns them as a new Instance of itself
	Array<T> cut(int begin, int end = -1){
		//assert((end > 1 || end == -1) && begin >= 0);
		if(end == -1 || end > length)end = length;
		//assert(end > begin);
		Array<T> res(end - begin);
		memcpy(res.adr, adr + begin, sizeof(T) * (end - begin));
		moveDown(begin, (end - begin));
		return res;
	}

	// void Array<T>::removeIndex(int Index)
	//		Removed a Array Element by its Index
	void removeIndex(int index){
		moveDown(index);
	}

	// int Array<T>::indexOf(T Element)
	//		Returns the Index of a Element in the Array. if it couldnt find one will return -1
	int indexOf(T element){
		for(uint i = 0; i < length; i++){
			if(adr[i] == element)return i;
		}
		return -1;
	}

	// bool Array<T>::find(T Element)
	//		Returns true if Element Exists in the Array.
	//		WARNING: Uses A Binary search. Array Must be Sorted to Work.
	bool find(T element){
		uint start = 0;
		uint end = length - 1;
		while(start != end){
			uint mid = start + ((end - start) / 2);

			if(element == adr[mid])return true;
			if(element < adr[mid]){
				end = mid;
			}
			if(element > adr[mid]){
				start = mid;
			}
		}
		return false;
	}


	//	Array<T> Array<T>::concat(const Array<T>& Data)
	//		Concatinates Another Array onto the End
	Array<T>& concat(const Array<T>& data) {
		push(data);
		return *this;
	}


	//------------PUSH--------------------------------------------------

	// void Array<T>::push(T Element)
	//		Pushes an Element onto the Back of an Array
	void push(const T& element) {
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

	//	void Array<T>::push(const Array<T>& Values)
	//		adds another array onto the end. Does the same as .concat
	void push(const Array<T>& values) {
		increase(values.length);
		memcpy(adr + (length), values.adr, sizeof(T) * values.length);
		length += values.length;
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
		length += (int)values.size();
	}

	// void Array<T>::insert(int Index, const Array<T>& Values)
	//		Inserts another Array into the Array at a certain Index
	void insert(int index, const Array<T>& values) {
		moveUp(index, values.length);
		memcpy(adr + index, values.adr, sizeof(T) * values.length);
		length += values.length;
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
		length += (int)values.size();
	}

	//	void Array<T>::unshift(const Array<T>& Values)
	//		adds another Array onto the front of the Array
	void unshift(const Array<T>& values) {
		moveUp(0, values.length);
		memcpy(adr, values.adr, sizeof(T) * values.length);
		length += values.length;
	}

	//------------------------------------------------------------------

	//T Array<T>::pop()
	//		Removes the Last Element of the Array and returns it
	//		WARNING: If the Array has no Elements it will throw an error.
	T pop() {
		//assert(length > 0);
		if (length <= 0)throw "Nothing Left to Pop";
		decrease();
		return adr[length];
	}

	//T Array<T>::shift()
	//		Removes the first Element of the Array and returns it
	//		WARNING: If the Array has no Elements it will throw an error.
	T shift() {
		//assert(length > 0);
		if (length <= 0)throw "Cannot Shift";
		T r = adr[0];
		moveDown(0);
		return r;
	}

	//	const T* Array<T>::data()
	//		Returns the Adress of the Array. Can be used to Memcpy or other
	const T* data() const {
		return adr;
	}

	//	int Array<T>::size()
	//		Returns the Length of the Array
	int size() {
		return length;
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Array<T>& data) {
	for (uint i = 0; i < data.length;) {
		T& e = data[i];
		os << '[' << i++ << ']' << " -> " << e << std::endl;
	}
	return os;

}

template<typename T>
std::ostream& operator<<(std::ostream& os, Array<T>&& data) {
	Array<T>* p = &data;
	os << *p;
	return os;
}