#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>

template<typename T>
class BitString
{
private:
	T data;
	int size;

public:
	BitString();
	BitString(T);
	T& refData();
	void printBitString();
};

template<typename T>
BitString<T>::BitString()
{
	data = T();
	size = sizeof(T);
};

template<typename T>
BitString<T>::BitString(T argData)
{
	data = argData;
	size = sizeof(T);
};

template<typename T>
T& BitString<T>::refData()
{
	return data;
};

template<typename T>
void BitString<T>::printBitString()
{
	const unsigned char mask = 0b10000000; //1000 0000
	const unsigned char* address = (unsigned char*)(&data);
	unsigned char bitString;

	for (int i = size - 1; i >= 0; i--)
	{
		bitString = *(address + i);

		for (int j = 0; j < 8; j++)
		{
			std::cout << ((mask & bitString)? '1': '0');
			bitString <<= 1;
		}
		std::cout << ' ';
	}
	std::cout << '\n';

	return;
};

#endif