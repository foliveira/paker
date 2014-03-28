#include "rle_comp.h"

RLE_Compress::RLE_Compress(OutStream *out, unsigned char prefixBits) : Compress(out) 
{
	assert(prefixBits <= 16);

	repBits = prefixBits;
	maxRep = (1 << prefixBits);
	rep = 0;
}

void RLE_Compress::putToken() 
{
	if(rep == 1) 
		out.putBit0();
	else 
	{ 
		out.putBit1(); 
		out.putBits((unsigned int)rep - 1, repBits); 
	}
	
	out.putByte(prevByte);
}

void RLE_Compress::putByte(int byte) 
{
	if (rep > 0) 
	{
		if(byte == prevByte && rep < maxRep) 
		{ 
			++rep; 
			return; 
		}
		
		putToken();
	}

	prevByte = byte;
	rep = 1;
}

void RLE_Compress::close() 
{
	if(rep > 0) 
	{ 
		putToken(); 
		rep = 0; 
	}
	
	Compress::close();
}

void RLE_Compress::putHeader(FileOutput &out) 
{
	out.putByte(repBits);
}