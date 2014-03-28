#ifndef LZSS_COMP_H
#define LZSS_COMP_H

#include "pk.h"
#include "Ringbuffer.h"

class LZSS_Compress : public Compress
{
	size_t posBits;
	size_t coincBits;

	Ringbuffer *rb;
public:
	LZSS_Compress(OutStream *, size_t, size_t);
	~LZSS_Compress(void);

	void putHeader(FileOutput&);
	void putByte(int byte);
	void putToken(void);
	void close(void);
};

#endif