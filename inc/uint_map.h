#ifndef UINT_MAP_H
# define UINT_MAP_H

# include "stdmap.h"

int		uint_map_add(stdmap* map, const char* key, unsigned int val);
int		uint_map_replace(stdmap* map, const char* key, unsigned int val);
int		uint_map_emplace_key(stdmap* map, const char* key, unsigned int val);
# define 	uint_map_remove map_remove

# define 	uint_map_get_size map_get_size
unsigned int	uint_get_value(const stdmap* map, const char* key);
# define 	uint_map_has_key map_has_key

# define 	uint_map_join map_join
# define 	uint_map_clear map_clear

stdmap* 	uint_map_new();
# define 	uint_map_copy map_copy
# define 	uint_map_delete map_delete

#endif //UINT_MAP_H
