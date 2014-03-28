#ifndef PK_H
#define PK_H

#include "File.h"
#include "BitStream.h"
#include "pkfile.h"

class Compress : public OutStreamFilter 
{
protected:
	BitOutStream out;
	Compress(OutStream *o) : OutStreamFilter(o), out(o) {}
public:
	void close() { out.close(); }
	virtual void putHeader(FileOutput &o) =0;
};

class Pk 
{
	FileInput in;
	FileOutput out;
	int mode;
public:
	Pk(const string &iName, const string &oName) : in(iName), out(oName) {}
	int init();
	void writeHeader(const string &ext);
	void go(int argc, char *args[], std::string&);
	void findMode(char *args[]);
};

#endif