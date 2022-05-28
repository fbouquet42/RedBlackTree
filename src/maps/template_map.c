#include "template_map.h"

#include <stdlib.h>

#define map_template_src(name, type) static void* copy##_##name(void* val) \
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

map_template_src(uchar, unsigned char)
map_template_src(char, char)
map_template_src(ushort, unsigned short)
map_template_src(short, short)
map_template_src(uint, unsigned int)
map_template_src(int, int)
map_template_src(float, float)
map_template_src(double, double)
