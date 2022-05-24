#include "rbt.h"
#include "stdmap.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

typedef struct	s_map_pair {
	char* key;
	void* val;
}		map_pair;

static int map_pair_pair_cmp(const void *elem1, const void* elem2)
{
	const map_pair* pair1 =  (map_pair*)elem1;
	const map_pair* pair2 =  (map_pair*)elem2;
	return strcmp((const char*)pair1->key, (const char*)pair2->key);
}

static int map_pair_key_cmp(const void *elem1, const void* key)
{
	const map_pair* pair1 =  (map_pair*)elem1;
	return strcmp((const char*)pair1->key, (const char*)key);
}

static void* new_pair(const char* key, void* val)
{
	map_pair*	pair;
	if(!(pair = (map_pair*)malloc(sizeof(map_pair))))
		return NULL;
	memset(pair, 0, sizeof(map_pair));

	char* allocated_key;
	if(!(allocated_key = (char*)malloc((strlen(key) + 1) * sizeof(char)))) {
		free(pair);
		return NULL;
	}
	memset(allocated_key, 0, sizeof(char) * strlen(key) + 1);
	strcpy(allocated_key, key);
	pair->key = allocated_key;
	pair->val = val;
	return pair;
}

int	add_key(stdmap* map, const char* key, void* val)
{
	map_pair*	pair;

	if(!(pair = new_pair(key, val)))
		return FALSE;

	red_black_tree* root = (red_black_tree*)map->root;

	if(!add_value(&root, (void*)pair, &map_pair_pair_cmp))
		return FALSE;
	map->size += 1;
	map->root = (void*)root;
	return TRUE;
}

int	replace_key(stdmap* map, const char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

int	append_key(stdmap* map, const char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

int	remove_key(stdmap* map, const char* key)
{
	red_black_tree* root = (red_black_tree*)map->root;
	if(!remove_value(&root, (const void*)key, &map_pair_key_cmp))
		return FALSE;
	map->size -= 1;
	map->root = (void*)root;
	return TRUE;
}

int	get_size(const stdmap* map)
{
	return map->size;
}

void*	get_key(const stdmap* map, const char* key)
{
	map_pair* pair;
	pair = (map_pair*)search_value((red_black_tree*)(map->root), (const void*)key, &map_pair_key_cmp);
	if(!pair)
		return NULL;
	return pair->val;
}

static void delete_pair(void* elem)
{
	map_pair* pair =  (map_pair*)elem;
	free(pair->key);
	free(pair->val);
	free(pair);
}

void	clear_map(stdmap* map)
{
	free_tree(map->root, &delete_pair);
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
