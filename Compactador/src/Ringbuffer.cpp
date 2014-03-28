#include "Ringbuffer.h"

Ringbuffer::Ringbuffer(size_t posBits, size_t coincBits)
{
	laSz = 1 << coincBits;
	rbSz = (1 << posBits) + laSz;

	start = 0;
	finish = 0;
	endTW = 0;
	itMax = 0;

	buffer = new unsigned char[rbSz];
	
	for(size_t i = 0; i < rbSz; ++i)
		buffer[i] = '\0';
}

Ringbuffer::~Ringbuffer(void)
{
	if(buffer)
		delete [] buffer;
}

size_t Ringbuffer::detectCollision(void)
{
	size_t pLA = endTW;
	size_t stt = start;
	int collisionCount = 0;
	int totalCollisions = 0;

	while(stt != endTW)
	{
		if(buffer[stt] == buffer[pLA])
		{
			size_t idx = stt;

			while(buffer[idx] == buffer[pLA] && pLA != finish)
			{
				incIdx(idx, 1);
				incIdx(pLA, 1);
				++collisionCount;
			}

			if(collisionCount >= MIN_COINCIDENCES && collisionCount > totalCollisions)
			{
				totalCollisions = collisionCount;
				itMax = stt;
			}
		}

		collisionCount = 0;
		incIdx(stt, 1);
		pLA = endTW;
	}

	return totalCollisions;
}

void Ringbuffer::doDecompression(size_t p, size_t c)
{
	size_t index = (finish + rbSz - p) % rbSz;

	while(c--)
	{
		putToken(getToken(index));
		incIdx(index, 1);
	}
}