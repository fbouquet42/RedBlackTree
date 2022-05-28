#ifndef TEMPLATE_MAP_H
# define TEMPLATE_MAP_H

# include "stdmap.h"

# define MAP_TEMPLATE_INC(name, type) \
int		name##_##map_add(stdmap* map, const char* key, type val); \
int		name##_##map_replace(stdmap* map, const char* key, type val); \
int		name##_##map_emplace_key(stdmap* map, const char* key, type val); \
type		name##_##get_value(const stdmap* map, const char* key); \
stdmap* 	name##_##map_new();

/*
 * Generics
 */
//int		map_remove(stdmap* map, const char* key);
//int		map_get_size(const stdmap* map);
//int		map_has_key(const stdmap* map, const char* key);
//int		map_join(stdmap* dest, stdmap* src);
//void		map_clear(stdmap* map);
//stdmap*	map_copy(stdmap* src);
//void		map_delete(stdmap* map);

MAP_TEMPLATE_INC(uchar, unsigned char)
MAP_TEMPLATE_INC(char, char)
MAP_TEMPLATE_INC(ushort, unsigned short)
MAP_TEMPLATE_INC(short, short)
MAP_TEMPLATE_INC(uint, unsigned int)
MAP_TEMPLATE_INC(int, int)
MAP_TEMPLATE_INC(float, float)
MAP_TEMPLATE_INC(double, double)

#endif //TEMPLATE_MAP_H
