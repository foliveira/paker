#include "rle_decomp.h"

void RLE_Decompress::getHeader(FileInput &in) 
{
	repBits = in.getByte();
}

int RLE_Decompress::getByte() 
{
	if (rep == 0) 
	{
		rep = in.getBit() ? in.getBits(repBits) + 1 : 1;
		
		assert(rep > 0);
		
		byte = in.getByte();
	}

	--rep;

	return byte;
}