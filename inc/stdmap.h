#ifndef STD_MAP_H
# define STD_MAP_H

struct s_rbt;

typedef struct	s_stdmap {
	void		*root;
	int		size;
}		stdmap;

int	add_key(stdmap* map, char* key, void* val);
int	replace_key(stdmap* map, char* key, void* val);
int	append_key(stdmap* map, char* key, void* val);

int	remove_key(stdmap* map, char* key);

int	get_size(const stdmap* map);
void*	get_key(const stdmap* map, char* key);

void	clear_map(stdmap* map);

char**	list_keys(stdmap* map);

stdmap* new_map();
void	delete_map(stdmap* map);

#endif //STD_MAP_H
