#include "template_map.h"

#include <stdlib.h>

#define MAP_TEMPLATE_SRC(name, type) static void* copy##_##name(void* val) \
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
type name##_##get_value(const stdmap* map, const char* key) \
{ \
	return *((type*)map_get_value(map, key)); \
}

MAP_TEMPLATE_SRC(uchar, unsigned char)
MAP_TEMPLATE_SRC(char, char)
MAP_TEMPLATE_SRC(ushort, unsigned short)
MAP_TEMPLATE_SRC(short, short)
MAP_TEMPLATE_SRC(uint, unsigned int)
MAP_TEMPLATE_SRC(int, int)
MAP_TEMPLATE_SRC(float, float)
MAP_TEMPLATE_SRC(double, double)
