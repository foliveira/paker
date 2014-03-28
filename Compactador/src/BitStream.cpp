#include "BitStream.h"
#include <assert.h>

inline void BitOutStream::put() 
{ 
	if(nBits == MAX_BITS) 
	{ 
		exit->putByte(bits); 
		nBits=0; 
	} 
}

void BitOutStream::putBit1() 
{ 
	bits <<= 1; 
	bits |= 1; 
	++nBits; 
	put(); 
#ifdef _DEBUG
	printf("1,");
#endif
}

void BitOutStream::putBit0() 
{ 
	bits <<= 1;
	++nBits; 
	put(); 
#ifdef _DEBUG
	printf("0,");
#endif
}

void BitOutStream::putBits(unsigned val, size_t len) 
{
#ifdef _DEBUG
	printf("%d,", val);
	if (len == 8) 
		printf("(%c)\n", val); 
#endif
	assert(exit);

	if(len < MAX_BITS-nBits) 
	{
		bits <<= len;
		bits |= val;
		nBits += len;
		return;
	}
	if(nBits > 0) 
	{
		size_t rest = MAX_BITS - nBits;
		bits <<= rest;
		bits |= (val >> (len-rest));
		exit->putByte(bits);
		len -= rest;
	}

	for(; len >= MAX_BITS ; len-=MAX_BITS)
		exit->putByte(val >> (len-MAX_BITS));

	nBits = len;
	bits = (Bits)val; 
}

void BitOutStream::close() 
{ 
	assert(exit);
	
	if(nBits>0) 
		exit->putByte(bits << (MAX_BITS-nBits));

	exit->close(); 
}

bool BitInStream::getBit() 
{
	assert(entry);

	if(nBits == 0) 
	{
		nBits = MAX_BITS;
		int c = entry->getByte();		

		assert(c != EOF);

		bits = (Bits)c;
	}

	bool res = (bits & 0x80) != 0;
	bits <<= 1;
	--nBits;

	return res;
}

unsigned BitInStream::getBits(size_t len) 
{
	assert(entry);
	// Esta implementação pode ser optimizada
	unsigned res = 0;
	for(; len>0 ; --len) 
	{
		res <<= 1;
		if(getBit()) 
			res |= 1;
	}

	return res;
}