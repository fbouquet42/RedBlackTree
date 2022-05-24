#include "rbt.h"
#include "stdmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct	s_map_pair {
	char* key;
	void* val;
}		map_pair;

static int map_pair_pair_cmp(const void *elem1, const void* elem2)
{
	map_pair* pair1 =  (map_pair*)elem1;
	map_pair* pair2 =  (map_pair*)elem2;
	return strcmp(pair1->key, pair2->key);
}

static int map_pair_key_cmp(const void *elem1, const void* key)
{
	map_pair* pair1 =  (map_pair*)elem1;
	return strcmp(pair1->key, key);
}

int	add_key(stdmap* map, char* key, void* val)
{
	map_pair* pair;

	if(!(pair = (map_pair*)malloc(sizeof(map_pair))))
		return FALSE;
	pair->key = key;
	pair->val = val;

	red_black_tree* root = (red_black_tree*)map->root;

	if(!add_value(&root, (void*)pair, &map_pair_pair_cmp))
		return FALSE;
	map->size += 1;
	map->root = (void*)root;
	return TRUE;
}

int	replace_key(stdmap* map, char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

int	append_key(stdmap* map, char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

int	remove_key(stdmap* map, char* key)
{
	red_black_tree* root = (red_black_tree*)map->root;
	if(!remove_value(&root, (void*)key, &map_pair_key_cmp))
		return FALSE;
	map->size -= 1;
	map->root = (void*)root;
	return TRUE;
}

int	get_size(const stdmap* map)
{
	return map->size;
}

void*	get_key(const stdmap* map, char* key)
{
	map_pair* pair;
	pair = (map_pair*)search_value((red_black_tree*)(map->root), (void*)key, &map_pair_key_cmp);
	if(!pair)
		return NULL;
	return pair->val;
}

void	clear_map(stdmap* map)
{
	free_tree(map->root);
	memset((void*)map, 0, sizeof(map));
}

stdmap*	new_map()
{
	stdmap* map;
	if(!(map = (stdmap*)malloc(sizeof(stdmap))))
		return NULL;
	memset((void*)map, 0, sizeof(stdmap));
	return map;
}

void	delete_map(stdmap* map)
{
	clear_map(map);
	free(map);
}
