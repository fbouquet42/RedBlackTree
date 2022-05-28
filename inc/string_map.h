#ifndef STRING_MAP_H
# define STRING_MAP_H

# include "stdmap.h"

int		string_map_add(stdmap* map, const char* key, char* val);
int		string_map_replace(stdmap* map, const char* key, char* val);
int		string_map_emplace_key(stdmap* map, const char* key, char* val);
char*		string_get_value(const stdmap* map, const char* key);
stdmap* 	string_map_new();

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

#endif //STRING_MAP_H
