#include "File.h"
//#include <string.h>

unsigned long FileInput::size() 
{
	assert(file);

	unsigned long pos = ftell(file);
	fseek(file, 0, SEEK_END);

	unsigned long total = ftell(file);
	fseek(file, pos, SEEK_SET);

	return total;
}

