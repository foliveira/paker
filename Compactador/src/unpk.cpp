#include "unpk.h"
#include "rle_decomp.h"
#include "lzss_decomp.h"
#include <iostream>
#include <string>
#include <memory.h>

using namespace std;

extern const char pk_id[NUMBER_OF_TYPES][4];
extern const char *pk;

int UnPk::init() 
{
	if(in.error()) 
	{ 
		cerr << "Erro ao abrir o ficheiro " << in.getName() << endl; 
		return 2; 
	}
	
	string ext;
	
	if(!readHeader(ext)) 
	{ 
		cerr << "Erro no header em " << in.getName() << endl; 
		return 4; 
	}

	FileName name = in.getName();
	
	name.removeExtension();
	name.addExtension(ext);
	
	out = new FileOutput(name);
	
	if(out->error()) 
	{ 
		cerr << "Erro ao abrir o ficheiro " << out->getName() << endl; 
		return 3; 
	}

	return 0;
}

bool UnPk::readHeader(string &ext) 
{
	char idr[sizeof(pk_id[0])];

	in.readBytes(idr, sizeof(idr));

	if(memcmp(idr, pk_id[0], sizeof(pk_id[0])) == 0)
		mode = 0;
	else if(memcmp(idr, pk_id[1], sizeof(pk_id[1])) == 0)
		mode = 1;
	else if(memcmp(idr, pk_id[2], sizeof(pk_id[2])) == 0)
		mode = 2;
	else
	{
		cout << "Argumentos inva'lidos." << endl;
		return false;
	}

	in.readBytes(&origSize, sizeof(origSize));

	char c; 
	
	ext.resize(0);
	
	while((c = in.getByte()) != 0) 
		ext += c;
	
	return true;
}

void UnPk::go() 
{
	Decompress *mainDecompressor;
	Decompress *auxiliaryDecompressor = 0;
	
	if(mode == 0)
		mainDecompressor = new RLE_Decompress(&in);
	else if(mode == 1)
		mainDecompressor = new LZSS_Decompress(&in);
	else
		mainDecompressor = new RLE_Decompress(auxiliaryDecompressor = new LZSS_Decompress(&in));

	mainDecompressor->getHeader(in);

	if(auxiliaryDecompressor)
		auxiliaryDecompressor->getHeader(in);

	for(; origSize > 0; --origSize)
		out->putByte(mainDecompressor->getByte());

	mainDecompressor->close();
	delete mainDecompressor;

	if(auxiliaryDecompressor)
		delete auxiliaryDecompressor;

	out->close();
}
