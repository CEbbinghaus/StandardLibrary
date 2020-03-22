#pragma once
#include <iostream>
#include <functional>
//#include <assert.h>

#define out std::cout
#define in std::cin
#define endl std::endl

/*
unshift	pushFront( value ) �add a new value to the front of the list
push	pushBack( value ) �add a new value to the end of the list
insert	insert( index, value ) �add a new value one-past the specified index location
first	first() �return the first element by value
last 	last() �return the last element by value
size	count() �return how many elements exist in the list
erase	erase( index ) �remove an element by its index
remove	remove( value ) �remove all elements with matching value
pop		popBack() �remove the last element
shift	popFront() �remove the first element
empty	empty() �return a Boolean, true if the list is empty, false otherwise
clear	clear() �remove all elements from the list
*/

namespace atyp {

	template<typename T>
	class List {
		class node {
		public:
			bool valid = true;
			node* next;
			node* previous;
			T data;
			int index = -1;
			
			
			// node() < No Arguments
			//- Creates a Node with No data and No Adress
			node() {
				next = nullptr;
				previous = nullptr;
			}
			// node(Bool Valid) < Placeholder Node with no Value
			//- Creates a Node with No data and No Adress
			node(bool) {
				valid = false;
				next = nullptr;
				previous = nullptr;
			}
			// node(T Value) < Value with no pointer
			//- Creates a new Node with only a Value and no Pointer
			node(T value) {
				next = nullptr;
				previous = nullptr;
				data = value;
			}
			// node(T value, node* adress) < Value with Pointer to next Node
			//- Creates a new Node in the middle with a value and a pointe to the next object
			node(T value, node* pAdress) {
				data = value;
				next = pAdress;
			}
			// node(T value, node* following, node* previous) < Value with Pointer to next Node
			//- Creates a new Node in the middle with a value and a pointe to the next object
			node(T value, node* pAdress, node* nAdress) {
				data = value;
				next = nAdress;
			}

			node& operator >> (node& other) {
				next = &other;
				other.previous = this;
				return *this;
			}

			operator T&(){
				return data;
			}
		};

		struct intermediate {
			intermediate(T& a_data, node* n) : data(a_data) {
				if (n->valid)d_node = n;
			}

			static node* d_node;
			T& data;
			int index = 0;

			operator T&() {
				return d_node->data;
			}
			operator node&(){
				return *d_node;
			}
		};

		class Iterator {
		public:
			int index = 0;
			node* prev;
			node* nxt;
			node* current;
			intermediate r;
			Iterator(node* ptr) : r(ptr->data, ptr), current(ptr), prev(ptr->previous), nxt(ptr->next){
				current->index = 0;
			};
			Iterator& operator++() {return (*(this))++;}
			Iterator& operator++(int) {
				index++;
				current = nxt;
				current->index = index;

				nxt = current->next;
				prev = current->previous;


				if (!(current->valid))return  * this;
				r.d_node = current;

				r.index = index;

				return *this;
			}
			bool operator!=(const Iterator& other) const { return other.current != current; }
			bool operator==(const Iterator& other) const { return other.current == current; }
			intermediate& operator*(){ return r; }
			//std::tuple<T&, int>& operator*() { return std::make_tuple<T&, int>(current->data, index); }
		};

		void insert(node* a, node* b, node* c) {
			*a >> *b;
			*b >> *c;
		}

		node* m_first;
		node* m_last;

		void clearData() {
			/*
			for (node& e : *this) {
				delete &e;
			}
			*/
			node* current = m_first->next;
			while (current != m_last) {
				node* tmp = current->next;
				delete current;
				current = tmp;
			}
		}

		int length;

	public:

		List() {
			m_first = new node(false);
			m_last = new node(false);
			*m_first >> *m_last;
			length = 0;
		}

		~List(){
			clearData();
			delete m_first;
			delete m_last;
		}

		T& operator[] (int index) {
			//assert(index < length);
			int i = 0;
			for (T& n : *this) {
				if (index == i)
					return n;
				++i;
			}
		}

		void insert(int index, T value) {
			//assert(index <= length);
			node* n = new node(value);
			int i = 0; 
			Iterator e = end();
			for (Iterator s = begin(); i < index; s++) {
				if (s == e || i == index) {
					node& current = *s;
					*(current.previous) >> *n;
					*n >> current;
					break;
				}
				i++;
			}
			++length;
		}

		void unshift(T value) {
			node* p = new node(value);
			node* second = m_first->next;
			*m_first >> *p;
			*p >> *second;
			++length;

		}
		void push(T value) {
			node* p = new node(value);
			node* secondlast = m_last->previous;
			*secondlast >> *p;
			*p >> *m_last;
			++length;
		}

		void erase(int index) {
			remove((*this)[index]);
			//node* n = (*this)[index];
			//node* prev = n->previous;
			//node* nxt = n->next;
			//*prev >> *nxt;
			//delete n;
		}

		void remove(T Value) {
			for (node& a : (*this)) {
				if (a.data == Value) {
					node* prev = a.previous;
					node* next = a.next;
					delete &a;
					*prev >> *next;
				}
			}
		}

		T shift() {
			node* r = m_first->next;
			T tmp = r->data;
			*m_first >> *r->next;
			delete r;
			return tmp;
		}

		T pop() {
			node* r = m_last->previous;
			T tmp = r->data;
			*r->previous >> *m_last;
			delete r;
			return tmp;
		}

		T& first(){
			if (!(m_first->next->valid))return *(T*)nullptr;
			return *(m_first->next);
		}

		T& last(){
			if (!(m_last->previous->valid))return *(T*)nullptr;
			return *(m_last->previous);
		}

		bool empty() {
			return m_first->next == m_last && m_last->previous == m_first;
		}

		void clear() {
			clearData();
			*m_first >> *m_last;
			length = 0;
		}

		int size() {
			return length;
		}
		
		Iterator begin() {
			return Iterator(m_first->next);
		}

		Iterator end() {
			return Iterator(m_last);
		}

		void forEach(std::function<void(T element, int index)> func) {
			for (auto&[element, index] : *this){
				func(element, index);
			}
		}
	};
	
	template<typename T>
	typename List<T>::node* List<T>::intermediate::d_node = nullptr;
	
		
	template<typename T>
	std::ostream& operator <<(std::ostream& output, List<T>& list){
		int i = 0;
		for (T& e : list) {
			output << '[' << i++ << ']' << " -> " << e << endl;
		}
		return output;
	}
	template<typename T>
	std::ostream& operator <<(std::ostream& output, List<T>&& list) {
		int i = 0;
		for (T& e : list) {
			output << '[' << i++ << ']' << " -> " << e << endl;
		}
		return output;
	}
}