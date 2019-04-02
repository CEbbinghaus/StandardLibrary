#pragma once
#include <iostream>
#include "Array.h"

namespace CLib {
	class String : public Array<char>{
	public: 
		String() {}
		String(char data[]) {
			length = (sizeof(data) / sizeof(data[0]));
			for (int i = 0; i < length; i++) {
				push(data[i]);
			}
		}
		String(int number) {
			int i = 10;
			for (; i < number; i *= 10) {
				int n = (int)floor(number % i / (i / 10));
				push(48 + n);
			}
		}

		String& operator =(char data[]) {
			length = (sizeof(data) / sizeof(data[0]));
			for (int i = 0; i < length; i++) {
				push(data[i]);
			}
		}

		String& operator =(std::string data) {
			length = (int)data.length();
			for (int i = 0; i < length; i++) {
				push(data[i]);
			}
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