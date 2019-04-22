#pragma once
#include <bitset>

namespace atyp {
	template<unsigned int amount>
	static std::bitset<amount> hash(void* data, unsigned int length) {
		std::bitset<amount> hash = 0;
		unsigned int salt[] = { 310501, 396547 , 553099 , 270493};
		unsigned int loops = length < amount ? amount * 5 : length * 3;

		unsigned int si = 1;
		unsigned int di = 1;
		unsigned int hi = 1;
		for (unsigned int i = 0; i < loops; i++) {
			unsigned int sp = si / (sizeof(salt) / sizeof(salt[0]));
			unsigned int sip = ((si - 1) % (sizeof(salt[0]) * 8));

			bool saltBit = salt[sp] & 0x1 << (sip - 1);

			bool dataBit = ((char*)data)[di / 8] & 0x1 << (di % 7);

			hash[hi] = saltBit ^ dataBit;

			++si; ++di; ++hi;

			hi %= amount - 1;
			di = ((di - 1) % length) + 1;
			si %= sizeof(salt) * 8;
		}
		return hash;
	}


	//class Hash {
	//	Hash(void* data, unsigned int length) {
	//	
	//	}
	//};
}