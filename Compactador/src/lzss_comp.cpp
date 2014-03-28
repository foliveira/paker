#include "lzss_comp.h"

LZSS_Compress::LZSS_Compress(OutStream *out, size_t pBits, size_t cBits) : Compress(out)
{
	assert(pBits >= cBits);

	posBits = pBits;
	coincBits = cBits;

	rb = new Ringbuffer(pBits, cBits);
}

LZSS_Compress::~LZSS_Compress(void)
{
	if(rb)
		delete rb;
}

void LZSS_Compress::putHeader(FileOutput &out)
{
	out.putByte(posBits);
	out.putByte(coincBits);
}

void LZSS_Compress::putByte(int byte)
{
	if(rb->isLookAheadFull())
		putToken();

	rb->putToken(byte);
}

void LZSS_Compress::putToken(void)
{
	size_t collisions;

	if(collisions = rb->detectCollision())
	{
		out.putBit1();
		out.putBits(rb->getDistance(), posBits);
		out.putBits(collisions - 1, coincBits);
		rb->incIdx(rb->getEndTextWindow(), collisions);
	}
	else
	{
		out.putBit0();
		out.putByte(rb->getEndToken());
		rb->incIdx(rb->getEndTextWindow(), 1);
	}
}

void LZSS_Compress::close(void)
{
	while(rb->getEndTextWindow() != rb->getBufferEndIndex())
		putToken();	

	Compress::close();
}