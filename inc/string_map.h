#ifndef STRING_MAP_H
# define STRING_MAP_H

# include "stdmap.h"

int		string_map_add(stdmap* map, const char* key, char* val);
int		string_map_replace(stdmap* map, const char* key, char* val);
int		string_map_emplace_key(stdmap* map, const char* key, char* val);
# define 	string_map_remove map_remove

# define 	string_map_get_size map_get_size
char*		string_get_value(const stdmap* map, const char* key);
# define 	string_map_has_key map_has_key

# define 	string_map_join map_join
# define 	string_map_clear map_clear

stdmap* 	string_map_new();
# define 	string_map_copy map_copy
# define 	string_map_delete map_delete

#endif //STRING_MAP_H
