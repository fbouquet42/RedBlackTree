#ifndef STD_MAP_H
# define STD_MAP_H

typedef struct s_stdmap stdmap;
typedef struct s_stdmap_it stdmap_it;


int		map_add_key(stdmap* map, const char* key, void* val);
int		map_replace_key(stdmap* map, const char* key, void* val); //TODO
int		map_append_key(stdmap* map, const char* key, void* val); //TODO
int		map_remove_key(stdmap* map, const char* key);

int		map_get_size(const stdmap* map);
void*		map_get_key(const stdmap* map, const char* key);

stdmap_it*		it_first(stdmap *map);
stdmap_it*		it_last(stdmap *map);
int			it_is_valid(stdmap_it* it);

void			it_next(stdmap_it* it);
void			it_previous(stdmap_it* it);
const char*		it_get_key(stdmap_it* it);
void*			it_get_value(stdmap_it* it);

void		clear_map(stdmap* map);

stdmap* 	new_map();
void		delete_map(stdmap* map);

#endif //STD_MAP_H
