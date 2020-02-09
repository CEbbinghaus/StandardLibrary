#pragma once
#include <bitset>
#include <type_traits>

namespace atyp {
	template<unsigned int bytes>
	class hash {
		class modifier {
			friend hash;
			hash* _data;
			unsigned int index;
			~modifier() {}
			modifier(hash* data) {
				_data = data;
				index = 0;
			}

			modifier& operator[](unsigned int a_index) {
				if (index >= bytes * CHAR_BIT)throw "Invalid Index";
				index = a_index;
				return *this;
			}
		  public:

			void ChangeHash(hash* data){
				_data = data;
			}

			modifier& operator = (bool value) {
				unsigned int x = index / CHAR_BIT;
				unsigned char y = index % CHAR_BIT;
				unsigned char& d = _data->_data[x];
				d = (d ^ (0b1 << y)) | value << y;
				return *this;
			}

			operator bool() {
				return _data->_data[index / CHAR_BIT] & (0b1 << (index % CHAR_BIT));
			}
		};

		modifier* _mod;
		unsigned char* _data;
		
	public:
		hash() {
			_data = new unsigned char[bytes];
			memset(_data, 0, bytes);
			_mod = new modifier(this);
			_mod->index = 0;
		}

		~hash() {
			if(_mod)
				delete _mod;
			if(_data)
				delete _data;
		}

		hash<bytes>& operator = (hash<bytes>& other){
			_data = new unsigned char[bytes];
			memcpy(_data, other.data(), bytes);
			_mod = new modifier(this);
			return *this;
		}
		
		hash<bytes>& operator = (hash<bytes>&& other){
			_mod = other._mod;
			_mod->ChangeHash(this);
			other._mod = nullptr;
			_data = other._data;
			other._data = nullptr;
			return *this;
		}

		bool all() {
			for (int i = 0; i < bytes; i++) {
				if (_data[i] ^ 0xFF)return false;
			}
			return true;
		}

		bool any() {
			for (int i = 0; i < bytes; i++) {
				if (_data[i])return true;
			}
			return false;
		}

		bool none() {
			for (int i = 0; i < bytes; i++) {
				if (_data[i])return false;
			}
			return true;
		}

		unsigned char* data() {
			return _data;
		}

		unsigned int bitCount() {
			unsigned int amount = 0;
			for (unsigned int i = 0; i < bytes; i++) {

				//Byte to retrieve the bit from
				char byte = _data[i];

				//Loops over every Bit in the Byte
				for(unsigned int b = 0; b < CHAR_BIT; ++b){

					//grabs the bit at the index of b and shifts it to the very right so it results in 0 if the bit is unset and 1 if its set
					amount += (byte & (0b1 << b)) >> b;
				}
			}
			return amount;
		}

		modifier& operator[](unsigned int index){
			return (*_mod)[index];
		}
	};

	template<typename T>
	T BitRotR(T v, unsigned char amount) {
		//if (!(std::is_integral<T>::value && std::is_unsigned<T>::value))throw "Type Must be a Unsigned Integral";
		return (v << amount) | ((unsigned)v >> (-amount & (sizeof(T) * CHAR_BIT - 1)));
	}

	template<typename T>
	T BitRotL(T v, unsigned char amount) {
		//if (!(std::is_integral<T>::value && std::is_unsigned<T>::value))throw "Type Must be a Unsigned Integral";
		return (v >> amount) | ((unsigned)v << (-amount & (sizeof(T) * CHAR_BIT - 1)));
	}

	template<unsigned int bytes>
	static std::bitset<bytes * 8> hearsum(const char* data, const unsigned int dLength) {
		std::bitset<bytes* CHAR_BIT> hash = 0;

		char salt[] = {(char)232, (char)253, (char)223};

		char*** snow = new char**[bytes]; // X = Bytes
		{
			unsigned int dataIndex = 0x333334;
			for (unsigned int x = 0; x < bytes; ++x) {
				snow[x] = new char* [dLength]; // Y = DataLength
				for (unsigned int y = 0; y < dLength; ++y) {
					snow[x][y] = new char[3]; //Z = 3
					for (unsigned int z = 0; z < 3; ++z) {
						dataIndex %= dLength;
						snow[x][y][z] = (data[dataIndex] ^ salt[(dataIndex + x) % 3]);
						++dataIndex;
					}
				}
			}
		}
		for (unsigned int x = 0; x < bytes; ++x) {
			for (unsigned int y = 0; y < dLength; ++y) {
				for (unsigned int z = 0; z < 3; ++z) {
					snow[x][y][z] ^= BitRotR(snow[(x + (bytes / 2)) % bytes][(y + (dLength / 2)) % dLength][(z + 2) % 3], 4);
				}
			}
		}

		for (unsigned int x = 0; x < bytes; ++x) {
			for (unsigned int y = 0; y < dLength; ++y) {
				for (int z = 1; z >= 0 ; --z) {
					snow[x][y][z] ^= (BitRotR(snow[x][y][z], 4) + BitRotR(snow[x][y][z + 1], 4)) + salt[(x * x) % 3];
				}
			}
			for (long long int y = (signed)dLength - 2; y >= 0; --y) {
				snow[x][y][0] ^= snow[x][y][0] + snow[x][y + 1][0];
			}
		}
		for (unsigned int i = 0; i < bytes * CHAR_BIT; ++i) {
			unsigned int c = i / CHAR_BIT;
			unsigned int b = i % CHAR_BIT;
			hash[i] = (bool)(snow[c][0][0] & (0b1 << b));
		}
		for (unsigned int x = 0; x < bytes; ++x) {
			for (unsigned int y = 0; y < dLength; ++y) {
				delete[] snow[x][y];
			}
			delete[] snow[x];
		}
		delete[] snow;
		return hash;
	}

	template<unsigned int bytes>
	static std::bitset<bytes * 8> hakret(const char* data, unsigned int dLength) {
		std::bitset<bytes * CHAR_BIT> hash = 0;
		unsigned char salt[] = { 233, 211, 239, 227, 251, 223, 229, 241 };
		{
			unsigned int si = 211;
			unsigned int di = 223;
			for (unsigned int i = 0; i < (bytes * CHAR_BIT); i++) {
				si %= (sizeof(salt) * CHAR_BIT);
				di %= (dLength * CHAR_BIT);
				hash[i] = hash[i] ^ (((BitRotR(salt[si / 8], i / bytes) ^ BitRotR(data[di / 8], i / bytes)) & (0b1 << si % 8)) >> (si % 8));
				++si;
				++di;
			}
		}
		//Initializing Registers and Filling them with Data
		unsigned int registerCount = (dLength / bytes | bytes);
		char** registers = new char*[registerCount];
		{
			unsigned dIndex = 0;
			for (unsigned int i = 0; i < registerCount; ++i) {
				registers[i] = new char[bytes];
				for (unsigned int j = 0; j < bytes; ++j) {
					dIndex %= dLength;
					registers[i][j] = BitRotR(data[dIndex], dIndex % 8) + 1;
					++dIndex;
				}
			}
		}

		for (unsigned int d = 0; d < dLength; d++) {
			for (unsigned int r = 0; r < registerCount; ++r) {
				for (unsigned int i = 0; i < bytes; i++) {
					registers[r][i] ^= (BitRotR(registers[r][(i + 5) % bytes], 2) ^ BitRotR(registers[r][(i + 5) % bytes], 4)) ^ (BitRotR(data[d], 4) ^ data[d]);
				}
			}
		}

		char final[bytes] = {0};
		for (unsigned int j = 0; j < bytes; ++j) {
			for (unsigned int i = 0; i < registerCount; ++i) {
				final[j] = BitRotL(final[j], 4) + registers[i][j];
			}
			for (int i = 0; i < CHAR_BIT; i++) {
				hash[j + i] = (final[j] & (0b1 << i));
			}
		}
		for (unsigned int i = 0; i < registerCount; i++) {
			delete[] registers[i];
		}
		delete[] registers;
		return hash;
	}
}