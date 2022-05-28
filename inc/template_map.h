#ifndef UINT_MAP_H
# define UINT_MAP_H

# include "stdmap.h"

# define map_template_inc(name, type) \
int		name##_##map_add(stdmap* map, const char* key, type val); \
int		name##_##map_replace(stdmap* map, const char* key, type val); \
int		name##_##map_emplace_key(stdmap* map, const char* key, type val); \
type		name##_##get_value(const stdmap* map, const char* key); \
stdmap* 	name##_##map_new();

/*
 * Generics
 */
//map_remove
//map_get_size
//map_has_key
//map_join
//map_clear
//map_copy
//map_delete

map_template_inc(uchar, unsigned char)
map_template_inc(char, char)
map_template_inc(ushort, unsigned short)
map_template_inc(short, short)
map_template_inc(uint, unsigned int)
map_template_inc(int, int)
map_template_inc(float, float)
map_template_inc(double, double)

#endif //UINT_MAP_H
