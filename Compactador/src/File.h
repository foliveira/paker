#ifndef FILE_H
#define FILE_H

#include "Stream.h"
#include <stdio.h>
#include <assert.h>
#include <string>

using std::string;

class FileName : public string 
{
public:
	FileName() {}
	FileName(const char *s) : string(s) {}
	FileName(const string &s) : string(s) {}
	string getBaseName() { size_t dotIdx = rfind('.'); return dotIdx != npos ? substr(0, dotIdx) : *this; }
	string getExtension() { size_t dotIdx = rfind('.'); return dotIdx != npos ? substr(dotIdx + 1) : ""; }
	void removeExtension() { size_t dotIdx = rfind('.'); if (dotIdx != npos) resize(dotIdx); }
	void addExtension(const string &ext) { (*this) += '.'; (*this) += ext; }
};

class FileBase 
{
protected:
	FILE *file;
	string name;
public:
	FileBase(const string &fileName, char *mode) : name(fileName) { file = fopen(fileName.c_str(), mode); }
	const string& getName() { return name; }
	bool error() { return file == 0; }
	void close() { if(file) fclose(file); }
};

class FileOutput : public FileBase, public OutStream 
{
public:
	FileOutput(const string &fileName) : FileBase(fileName, "wb") {}
	void putByte(int b)	{ assert(file); fputc(b, file); }
	void close() { FileBase::close(); }
	void writeBytes(void *ptr, size_t size) { assert(file); fwrite(ptr, size, 1, file); }
};

class FileInput : public FileBase, public InStream 
{
public:
	FileInput(const string &fileName) : FileBase(fileName, "rb") {}
	int getByte() {  assert(file); return fgetc(file); }
	void close() { FileBase::close(); }
	void readBytes(void *ptr, size_t size) { assert(file); fread(ptr, size, 1, file); }
	unsigned long size();
};

#endif