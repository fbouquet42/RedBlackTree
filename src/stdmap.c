#include "rbt.h"
#include "stdmap.h"

#include <stdlib.h>
#include <string.h>

typedef struct	s_stdmap_type {
	map_free_type	ffree;
	map_copy_type	fcpy;
}		stdmap_type;

typedef struct	s_stdmap_it {
	red_black_tree	*index;
}		stdmap_it;

typedef struct	s_stdmap {
	red_black_tree	*root;
	map_free_type	ffree;
	map_copy_type	fcpy;
	stdmap_it	*iterator;
	int		size;
}		stdmap;

typedef struct	s_map_pair {
	char* key;
	void* val;
}		map_pair;

void	pair_delete(void* elem)
{
	map_pair* pair =  (map_pair*)elem;
	free(pair->key);
	free(pair->val);
	free(pair);
}

int	map_is_valid(stdmap* map)
{
	return tree_is_valid(map->root);
}

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

static void* pair_new(const char* key, void* val)
{
	map_pair*	pair;
	if(!(pair = (map_pair*)malloc(sizeof(map_pair))))
		return NULL;
	memset(pair, 0, sizeof(map_pair));

	char*	allocated_key;
	int	len = strlen(key);
	if(!(allocated_key = (char*)malloc((len + 1) * sizeof(char)))) {
		free(pair);
		return NULL;
	}
	strcpy(allocated_key, key);
	allocated_key[len] = '\0';
	pair->key = allocated_key;
	pair->val = val;
	return pair;
}

int	map_add(stdmap* map, const char* key, void* val)
{
	map_pair*	pair;

	if(!(pair = pair_new(key, val)))
		return FALSE;

	red_black_tree* root = map->root;

	if(!add_value(&root, (void*)pair, &map_pair_pair_cmp, map->ffree))
		return FALSE;
	map->size += 1;
	map->root = root;
	map->iterator->index = NULL;
	return TRUE;
}

int	map_emplace(stdmap* map, const char* key, void* val)
{
	map_pair*	pair;

	if(!(pair = pair_new(key, val)))
		return FALSE;

	red_black_tree* root = map->root;
	int		ret;

	ret = emplace_value(&root, (void*)pair, &map_pair_pair_cmp, map->ffree);

	if(ret == FALSE)
		return FALSE;
	else if(ret == LEAF_REPLACED)
		return TRUE;
	map->size += 1;
	map->root = root;
	map->iterator->index = NULL;
	return TRUE;
}

int	map_replace(stdmap* map, const char* key, void* val)
{
	map_pair*	pair;

	if(!(pair = pair_new(key, val)))
		return FALSE;

	red_black_tree* root = map->root;
	if(!replace_value(&root, (void*)pair, &map_pair_pair_cmp, map->ffree))
		return FALSE;
	return TRUE;
}

int	map_remove(stdmap* map, const char* key)
{
	red_black_tree* root = map->root;
	if(!remove_value(&root, (const void*)key, &map_pair_key_cmp, map->ffree))
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

void*	map_get_value(const stdmap* map, const char* key)
{
	red_black_tree* leaf;
	map_pair* pair;

	leaf = search_leaf((red_black_tree*)(map->root), (const void*)key, &map_pair_key_cmp);
	if(!leaf)
		return NULL;
	pair = (map_pair*)leaf->data;
	if(!pair)
		return NULL;
	return pair->val;
}

int	map_has_key(const stdmap* map, const char* key)
{
	if(search_leaf((red_black_tree*)(map->root), (const void*)key, &map_pair_key_cmp))
		return TRUE;
	return FALSE;
}

void	map_clear(stdmap* map)
{
	free_tree(map->root, map->ffree);
	map->root = NULL;
	map->iterator = NULL;
	map->size = 0;
}

int             map_join(stdmap* dest, stdmap* src)
{
	if(dest->ffree != src->ffree || dest->fcpy != src->fcpy)
		return FALSE;
	stdmap_it* it = it_first(src);
	void* val;
	while(it_is_valid(it)) {
		if(!(val = dest->fcpy(it_get_value(it))))
			return FALSE;
		map_emplace(dest, it_get_key(it), val);
		it_next(it);
	}
	return TRUE;
}

stdmap*         map_copy(stdmap* src)
{
	stdmap* dest = map_new(src->ffree, src->fcpy);
	if(!dest)
		return NULL;
	if(!map_join(dest, src)) {
		map_delete(dest);
		return NULL;
	}
	return dest;
}

stdmap*	map_new(map_free_type ffree, map_copy_type fcpy)
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
	map->ffree = ffree;
	map->fcpy = fcpy;
	return map;
}

void	map_delete(stdmap* map)
{
	map_clear(map);
	free(map->iterator);
	free(map);
}
