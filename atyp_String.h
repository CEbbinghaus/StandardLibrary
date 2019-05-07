#pragma once
#include <iostream>
//#include "Array.h"

namespace atyp {
	class String{
		char* adr = nullptr;
		int m_size = 0;
		unsigned int length = 0;

	protected:
		//Ensures there is always memory to write to. Allocates More memory if Nessecary
		void increase(int amount = 1) {
			//Assert(m_size >= length, "TESTING")
			if ((length + amount) > m_size) {
				m_size = (m_size + amount) * 2;
				char* tmp = (char*)malloc(sizeof(char) * m_size);
				memcpy(tmp, adr, sizeof(char) * length);
				if (adr != nullptr)delete[] adr;
				adr = tmp;
			}
		}

		//Ensures that the Array is Able to Decrease size
		void decrease(int amount = 1) {
			//Assert(m_size >= 0, "TESTING")
		}

		//Shifts all Array elements Up to make space for more
		void moveUp(int begin, int amount = 1) {
			increase(amount);
			memmove(adr + (begin + amount), adr + begin, sizeof(char) * (length - begin));
		}

		//Shifts all Elements down to compress the array
		void moveDown(int begin, int amount = 1) {
			decrease(amount);
			memcpy(adr + begin, adr + begin + amount, sizeof(char) * length);
		}
	public: 
		String() {}
		String(char data[]) {
			int size = (sizeof(data) / sizeof(data[0]));
			increase(length);
			memcpy(adr + length, &data, sizeof(char) * size);
			length += size;
		}
		String(int number) {
			int i = 10;
			for (; i < number; i *= 10) {
				int n = (int)floor(number % i / (i / 10));
				increase();
				adr[length] = 48 + n;
				length++;
			}
		}

		char* data() {
			return adr;
		}

		unsigned int length() {
			return length;
		}

		String& operator =(char data[]) {
			unsigned int size = (sizeof(data) / sizeof(data[0]));
			increase(size);
			memcpy(adr,&data, sizeof(char) * size);
		}

		String& operator =(std::string data) {
			unsigned int size = (unsigned int)data.length();
			increase(size);
			memcpy(adr, data.data(), sizeof(char) * size);
		}

		String& operator =(String data) {
			unsigned int size = data.length;
			increase(size);
			memcpy(adr, data.data(), sizeof(char) * size);
		}

		String& operator +=(char data[]) {
			return *this;
		}

		String& operator +=(std::string data) {
			return *this;
		}
	};

	std::ostream& operator << (std::ostream& os, String& data) {
		os << "\"";
		return os;
	}

	std::ostream& operator << (std::ostream& os, String&& data) {
		String t = data;
		return os << data;
	}
}