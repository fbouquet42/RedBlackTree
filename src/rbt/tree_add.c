#include "rbt.h"

#include <stdlib.h>
#include <string.h>

int tree_add(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;

	if(!*root) {
		if(!(leaf = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return FALSE;
		memset(leaf, 0, sizeof(red_black_tree));
		leaf->color = Black;
		leaf->data = value;
		*root = leaf;
		return TRUE;
	}

	leaf = *root;
	while(leaf) {
		if(fc(leaf->data, value) > 0) {
			if(!leaf->left) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->left = son;
				break;
			}
			else
				leaf = leaf->left;
		}
		else if(fc(leaf->data, value) < 0) {
			if(!leaf->right) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->right = son;
				break;
			}
			else
				leaf = leaf->right;
		}
		else {
			ff(value);
			return FALSE;
		}
	}

	*root = tree_resolve_double_red(leaf);

	return TRUE;
}
