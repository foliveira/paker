#ifndef RLE_COMP_H
#define RLE_COMP_H

#include "pk.h"

class RLE_Compress : public Compress 
{
	unsigned char repBits;
	size_t maxRep;
	unsigned char prevByte;
	size_t rep;

	void putToken();
public:
	RLE_Compress(OutStream *out, unsigned char repBits);
	void putHeader(FileOutput &out);
	void putByte(int byte);
	void close();
};
#endif