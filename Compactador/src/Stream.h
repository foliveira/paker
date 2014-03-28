#ifndef STREAM_H
#define STREAM_H

#include <stdio.h>

class OutStream								// Interface				
{ 
public:										//	 bytes	+-----------
	virtual void putByte(int) =0;			//	>>----->| OutStream 
	virtual void close() =0;				//			+-----------
	virtual ~OutStream() {}
};

class OutStreamFilter :	public OutStream 
{
protected:
	OutStream *exit;
	OutStreamFilter(OutStream *out) : exit(out) {}
public:
	void putByte(int byte) { exit->putByte(byte); }
	void close() { exit->close(); }
};


class InStream								// Interface
{ 
public:										//  ---------+ bytes
	virtual int getByte() =0;				//  InStream |------>>
	virtual void close() =0;				//  ---------+
	virtual ~InStream() {}
};

class InStreamFilter : public InStream 
{
protected:
	InStream *entry;
	InStreamFilter(InStream *in) : entry(in) {}
public:
	int getByte() { return entry->getByte(); }
	void close() { entry->close(); }
};

#endif
