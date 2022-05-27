#include "uint_map.h"

#include <stdlib.h>

static void* copy_uint(void* uvalue)
{
	unsigned int* new_uvalue;

	if(!(new_uvalue = (unsigned int*)malloc(sizeof(unsigned int))))
		return NULL;
	*new_uvalue = *((unsigned int*)uvalue);
	return (void*)new_uvalue;
}

int uint_map_add(stdmap* map, const char* key, unsigned int val)
{
	void*	cpy;
	if(!(cpy = copy_uint(&val)))
		return 0;
	return map_add(map, key, cpy);
}

int uint_map_replace(stdmap* map, const char* key, unsigned int val)
{
	void*	cpy;
	if(!(cpy = copy_uint(&val)))
		return 0;
	return map_replace(map, key, cpy);
}

stdmap*	uint_map_new()
{
	return map_new(&pair_delete, &copy_uint);
}

unsigned int uint_get_value(const stdmap* map, const char* key)
{
	return *((unsigned int*)map_get_value(map, key));
}
