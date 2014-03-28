#ifndef UNPK_H
#define UNPK_H

#include "File.h"
#include "BitStream.h"
#include "pkfile.h"

class Decompress : public InStreamFilter 
{
protected:
	BitInStream in;
	Decompress(InStream *i) : InStreamFilter(i), in(i) {}
public:
	void close() { in.close(); }
	virtual void getHeader(FileInput &i) =0;
};

class UnPk 
{
	FileInput in;
	FileOutput *out;
	unsigned long origSize;
	int mode;
public:
	UnPk(const string &iName) : in(iName), out(0) {}
	~UnPk() { if(out) delete out; }
	int init();
	unsigned long originalSize() { return origSize; }
	bool readHeader(string &ext);
	void go();
};

#endif