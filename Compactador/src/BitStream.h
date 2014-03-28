#ifndef BITSTREAM_H
#define BITSTREAM_H

#include "Stream.h"

class BitBuffer 
{
protected:
	typedef unsigned char Bits;
	static const int MAX_BITS = 8;
	Bits bits;
	size_t nBits;
	BitBuffer(): nBits(0) {}
};

class BitOutStream : public OutStreamFilter, public BitBuffer 
{
	void put();
public:
	BitOutStream(OutStream *exit) : OutStreamFilter(exit) {}
	void putBit0();
	void putBit1();
	void putBits(unsigned, size_t);
	void putByte(int byte) { putBits(byte, 8); }
	void close();
};

class BitInStream : public InStreamFilter, public BitBuffer 
{
public:
	BitInStream(InStream *entry) : InStreamFilter(entry) {}
	bool getBit();
	unsigned getBits(size_t);
	int getByte() { return getBits(8); }
};

#endif