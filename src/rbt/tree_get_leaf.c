#include "rbt.h"

red_black_tree* tree_get_leaf(red_black_tree* leaf, const void* value, function_to_compare f)
{
	while(leaf) {
		if(f(leaf->data, value) > 0)
			leaf = leaf->left;
		else if(f(leaf->data, value) < 0)
			leaf = leaf->right;
		else
			break;
	}
	return leaf;
}
