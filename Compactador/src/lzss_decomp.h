#ifndef LZSS_DECOMP_H
#define LZSS_DECOMP_H

#include "unpk.h"
#include "Ringbuffer.h"

class LZSS_Decompress : public Decompress
{
	size_t nextToken;
	size_t pBits;
	size_t cBits;
	Ringbuffer *rb;
public:
	LZSS_Decompress(InStream*);
	~LZSS_Decompress(void);
	void getHeader(FileInput&);
	int getByte(void);
	void close(void);
};

#endif