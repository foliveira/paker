#include "lzss_decomp.h"

LZSS_Decompress::LZSS_Decompress(InStream *i) : Decompress(i)
{
	nextToken = 0;
}

LZSS_Decompress::~LZSS_Decompress(void)
{
	if(rb)
		delete rb;
}

void LZSS_Decompress::getHeader(FileInput &i)
{
	pBits = i.getByte();
	cBits = i.getByte();

	rb = new Ringbuffer(pBits, cBits);
}

int LZSS_Decompress::getByte(void)
{
	if(nextToken == rb->getBufferEndIndex())
	{
		if(in.getBit())
		{
			size_t pos = in.getBits(pBits);
			size_t coinc = in.getBits(cBits) + 1;

			rb->doDecompression(pos, coinc);
		}
		else
			rb->putToken(in.getBits(8));
	}

	unsigned char token = rb->getToken(nextToken);
	rb->incIdx(nextToken, 1);

	return token;
}

void LZSS_Decompress::close(void)
{
	Decompress::close();
}