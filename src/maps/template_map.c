#include "uint_map.h"

#include <stdlib.h>

#define map_template(name, type) static void* copy##_##name(void* val) \
{ \
	type* new_val; \
 \
	if(!(new_val = (type*)malloc(sizeof(type)))) \
		return NULL; \
	*new_val = *((type*)val); \
	return (void*)new_val; \
} \
 \
int name##_##map_add(stdmap* map, const char* key, type val) \
{ \
	void*	cpy; \
	if(!(cpy = copy##_##name(&val))) \
		return 0; \
	return map_add(map, key, cpy); \
} \
 \
int name##_##map_replace(stdmap* map, const char* key, type val) \
{ \
	void*	cpy; \
	if(!(cpy = copy##_##name(&val))) \
		return 0; \
	return map_replace(map, key, cpy); \
} \
 \
stdmap*	name##_##map_new() \
{ \
	return map_new(&pair_delete, &copy##_##name); \
} \
 \
unsigned int name##_##get_value(const stdmap* map, const char* key) \
{ \
	return *((type*)map_get_value(map, key)); \
}

map_template(uchar, unsigned char)
map_template(char, char)
map_template(ushort, unsigned short)
map_template(short, short)
map_template(uint, unsigned int)
map_template(int, int)
map_template(float, float)
map_template(double, double)
