#ifndef PKFILE_H
#define PKFILE_H

#define NUMBER_OF_TYPES 3

static const char pk_id[NUMBER_OF_TYPES][4] = { 
	{'P', 'K', '1', 0}, 
	{'P', 'K', '2', 0}, 
	{'P', 'K', '*', 0} 
};

static const char *pk_ext = "pk";

#endif