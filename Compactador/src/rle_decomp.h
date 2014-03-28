#ifndef RLE_DECOMP_H
#define RLE_DECOMP_H

#include "unpk.h"

class RLE_Decompress : public Decompress 
{
	unsigned char repBits;
	unsigned char byte;
	size_t rep;

public:
	RLE_Decompress(InStream *i) : Decompress(i), rep(0) {}
	void getHeader(FileInput &in);
	int getByte();
};

#endif