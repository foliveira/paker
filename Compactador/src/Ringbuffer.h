#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#define MIN_COINCIDENCES 2

class Ringbuffer
{
	size_t rbSz;
	size_t laSz;

	size_t start;
	size_t finish;

	size_t endTW;
	size_t itMax;

	unsigned char *buffer;
public:
	Ringbuffer(size_t, size_t);
	~Ringbuffer(void);
	size_t detectCollision(void);
	void doDecompression(size_t, size_t);
	
	inline bool isLookAheadFull(void) { return ((endTW + laSz) % rbSz) == finish; }

	inline size_t getDistance(void) { return (endTW - itMax) < 0 ? endTW + (rbSz - itMax) : endTW - itMax; }
	inline size_t& getEndTextWindow(void) { return endTW; }
	inline size_t& getBufferEndIndex(void) { return finish; }

	inline unsigned char getEndToken(void) { return buffer[endTW]; }
	inline unsigned char getToken(size_t index) { return buffer[index]; }


	inline void incIdx(size_t &idx, size_t jump) const { idx = (idx + jump) % rbSz; } 
	inline void putToken(unsigned char token) { buffer[finish] = token; incIdx(finish, 1); }
};

#endif