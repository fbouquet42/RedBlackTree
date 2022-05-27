#ifndef STD_MAP_H
# define STD_MAP_H

typedef void	(*map_free_type) (void*type);
typedef void*	(*map_copy_type) (void*type);

typedef struct s_stdmap stdmap;
typedef struct s_stdmap_it stdmap_it;

int	map_is_valid(stdmap* map);

void		pair_delete(void* elem);

int		map_add(stdmap* map, const char* key, void* val);
int		map_replace(stdmap* map, const char* key, void* val);
int		map_emplace(stdmap* map, const char* key, void* val);
int		map_remove(stdmap* map, const char* key);

int		map_get_size(const stdmap* map);
void*		map_get_value(const stdmap* map, const char* key);
int		map_has_key(const stdmap* map, const char* key);

stdmap_it*	it_first(stdmap *map);
stdmap_it*	it_last(stdmap *map);
int		it_is_valid(stdmap_it* it);

void		it_next(stdmap_it* it);
void		it_previous(stdmap_it* it);
const char*	it_get_key(stdmap_it* it);
void*		it_get_value(stdmap_it* it);

int		map_join(stdmap* dest, stdmap* src);
void		map_clear(stdmap* map);

stdmap* 	map_new(map_free_type ffree, map_copy_type fcpy);
stdmap*		map_copy(stdmap* src);
void		map_delete(stdmap* map);

#endif //STD_MAP_H
