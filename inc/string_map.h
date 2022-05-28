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
//map_remove
//map_get_size
//map_has_key
//map_join
//map_clear
//map_copy
//map_delete

#endif //STRING_MAP_H
