#ifndef STRING_MAP_H
# define STRING_MAP_H

# include "stdmap.h"

int		string_map_add(stdmap* map, const char* key, char* val);
int		string_map_replace(stdmap* map, const char* key, char* val);
int		string_map_emplace_key(stdmap* map, const char* key, char* val);
char*		string_get_value(const stdmap* map, const char* key);
stdmap* 	string_map_new();

char*		it_get_value_as_string(stdmap_it* it);

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
//
//stdmap_it*	it_first(stdmap *map);
//stdmap_it*	it_last(stdmap *map);
//int		it_is_valid(stdmap_it* it);
//void		it_next(stdmap_it* it);
//void		it_previous(stdmap_it* it);
//const char*	it_get_key(stdmap_it* it);

#endif //STRING_MAP_H
