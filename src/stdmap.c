#include "rbt.h"
#include "stdmap.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

typedef struct	s_stdmap_it {
	red_black_tree	*index;
}		stdmap_it;

typedef struct	s_stdmap {
	red_black_tree	*root;
	stdmap_it	*iterator;
	int		size;
}		stdmap;

typedef struct	s_map_pair {
	char* key;
	void* val;
}		map_pair;

stdmap_it*	it_first(stdmap* map) {
	map->iterator->index = map->root;
	return map->iterator;
}

stdmap_it*	it_last(stdmap* map) {
	red_black_tree* last = map->root;
	if(last) {
		while(last->right)
			last = last->right;
		while(last->left)
			last = last->left;
	}
	map->iterator->index = last;
	return map->iterator;
}

void		it_next(stdmap_it* it) {
	if(it->index->left) {
		it->index = it->index->left;
	}
	else if (it->index->right) {
		it->index = it->index->right;
	}
	else {
		red_black_tree *from;
		while(it->index) {
			from = it->index;
			it->index = it->index->parent;
			if(!it->index)
				return;
			if(it->index->right && it->index->right != from) {
				it->index = it->index->right;
				return;
			}
		}
	}
}

void		it_previous(stdmap_it* it)
{
	red_black_tree *from;
	from = it->index;

	it->index = it->index->parent;
	if(!it->index)
		return;
	if(it->index->left && it->index->right == from) {
		it->index = it->index->left;
		while(it->index->right)
			it->index = it->index->right;
		while(it->index->left)
			it->index = it->index->left;
	}
	else
		return;
}

int		it_is_valid(stdmap_it* it)
{
	return (it->index) ? TRUE : FALSE;
}

const char*	it_get_key(stdmap_it* it)
{
	map_pair* pair;

	pair = (map_pair*)it->index->data;

	return (const char*)(pair->key);
}

void*		it_get_value(stdmap_it* it)
{
	map_pair* pair;

	pair = (map_pair*)it->index->data;

	return (void*)(pair->val);
}

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

int	map_add_key(stdmap* map, const char* key, void* val)
{
	map_pair*	pair;

	if(!(pair = new_pair(key, val)))
		return FALSE;

	red_black_tree* root = map->root;

	if(!add_value(&root, (void*)pair, &map_pair_pair_cmp))
		return FALSE;
	map->size += 1;
	map->root = root;
	map->iterator->index = NULL;
	return TRUE;
}

int	map_replace_key(stdmap* map, const char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

int	map_append_key(stdmap* map, const char* key, void* val)
{
	(void)map;
	(void)key;
	(void)val;
	return FALSE;
}

static void delete_pair(void* elem)
{
	map_pair* pair =  (map_pair*)elem;
	free(pair->key);
	free(pair->val);
	free(pair);
}

int	map_remove_key(stdmap* map, const char* key)
{
	red_black_tree* root = map->root;
	if(!remove_value(&root, (const void*)key, &map_pair_key_cmp, &delete_pair))
		return FALSE;
	map->size -= 1;
	map->root = root;
	map->iterator->index = NULL;
	return TRUE;
}

int	map_get_size(const stdmap* map)
{
	return map->size;
}

void*	map_get_key(const stdmap* map, const char* key)
{
	map_pair* pair;
	pair = (map_pair*)search_value((red_black_tree*)(map->root), (const void*)key, &map_pair_key_cmp);
	if(!pair)
		return NULL;
	return pair->val;
}

void	clear_map(stdmap* map)
{
	free_tree(map->root, &delete_pair);
	map->root = NULL;
	map->size = 0;
}

stdmap*	new_map()
{
	stdmap* map;
	if(!(map = (stdmap*)malloc(sizeof(stdmap))))
		return NULL;
	stdmap_it* it;
	if(!(it = (stdmap_it*)malloc(sizeof(stdmap_it))))
	{
		free(map);
		return NULL;
	}
	memset((void*)map, 0, sizeof(stdmap));
	memset((void*)it, 0, sizeof(stdmap_it));
	map->iterator = it;
	return map;
}

void	delete_map(stdmap* map)
{
	clear_map(map);
	free(map->iterator);
	free(map);
}
