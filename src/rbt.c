#include "rbt.h"

#include <stdlib.h>
#include <string.h>

static red_black_tree* rebalance_tree(red_black_tree* root, void* value, function_to_compare f)
{
	(void)value;
	(void)f;
	return root;
}

static int insert_red_element(red_black_tree* parent, void* value, function_to_compare f)
{
	if(f(parent->data, value) > 0) {
		if(!parent->left) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return FALSE;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = parent;
			parent->left = son;
			return TRUE;	
		}
		return insert_red_element(parent->left, value, f);
	}
	else if(f(parent->data, value) < 0) {
		if(!parent->right) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return FALSE;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = parent;
			parent->right = son;
			return TRUE;	
		}
		return insert_red_element(parent->right, value, f);
	}
	else
		return FALSE;
}

red_black_tree *add_value(red_black_tree* root, void* value, function_to_compare f)
{
	red_black_tree* son;

	if(!root) {
		if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return NULL;
		memset(son, 0, sizeof(red_black_tree));
		son->color = Black;
		son->data = value;
		return son;
	}

	if(!insert_red_element(root, value, f))
		return NULL;

	return rebalance_tree(root, value, f);
}
