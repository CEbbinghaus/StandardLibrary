#pragma once
#include <type_traits>

namespace atyp {
	//template<typename T>
	//class BinaryTree {
	//	class Node {
	//		Node* l;
	//		Node* r;
	//		T* data;
	//	};
	//	
	//	T add(const T& a, const T& b) const
	//	{
	//		return a + b;
	//	}


	//	template<typename T>
	//	typename std::enable_if_t<
	//		std::disjunction<std::is_integer_v<T>, std::is_real_v<T>>>
	//	T add(const int a_int_a, const int a_int_b) const
	//	{
	//		return a_int_a + a_int_b;
	//	}

	//	//void doSomething(T * v);
	//	//
	//	//template <std::vector<int>>
	//	//void doSomething(std::vector<int> * v)
	//};
	
	class BinaryTree{
		class Node{
		public:
			Node* l = nullptr;
			Node* r = nullptr;
			Node* p = nullptr;
			int v = 0;
			Node(int value, Node* parent){
				p = parent;
				v = value;
			}
			~Node(){
				delete l;
				delete r;
			}
			bool empty(){
				return (l == nullptr && r == nullptr);
			}
			void add(const int& value){
				if(value < v){
					if(l)l->add(value);
					else l = new Node(value, this);
				}
				else{
					if(r)r->add(value);
					else r = new Node(value, this);
				}
			}
			Node*& operator[] (const char side){
				if(side == 'l')return l;
				if(side == 'r')return r;
				return p;
			}
		};

		Node* root = nullptr;

		char nt(char value, char val1, char val2){
			if(value == val1)return val2;
			return val1;
		}
	public:
		BinaryTree(){}
		~BinaryTree(){
			delete root;
		}
		void push(int value) {
			if (root)root->add(value);
			else root = new Node(value, nullptr);
		}
 		bool find(int value) {
			Node* current = root;
			while (current != nullptr) {
				if (value == current->v)return true;
				if (value < current->v) {
					current = current->l;
				}
				else {
					current = current->r;
				}
			}
			return false;
		}
		void remove(int value) {
			Node* current = root;
			bool found = false;
			while (current != nullptr) {
				if (value == current->v) {
					unsigned short children = (current->l ? (current->r ? 2 : 1) : (current->r ? 1 : 0));
					Node* parent = current->p;

					switch (children)
					{
					case 0:
						(current->p->l == current ? current->p->l : current->p->r) = nullptr;
						current->l = current->r = nullptr;
						delete current;
						return;
					case 1:
						(current->p->l == current ? current->p->l : current->p->r) = (current->l ? current->l : current->r);
						current->l = current->r = nullptr;
						delete current;
						return;
					case 2:
						Node* pathNode = current->r;

						while (pathNode->l != nullptr) {
							pathNode = pathNode->l;
						}

						pathNode->p->l = pathNode->r;
						current->v = pathNode->v;
						pathNode->l = pathNode->r = nullptr;
						delete pathNode;
						return;
					}
				}
				if (value < current->v)
					current = current->l;
				else
					current = current->r;
			}
			return;
		}
	};
}