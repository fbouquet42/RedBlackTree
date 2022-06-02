#include "rbt.h"

int tree_replace(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;
	leaf = *root;
	while(leaf) {
		if(fc(leaf->data, value) > 0)
			leaf = leaf->left;
		else if(fc(leaf->data, value) < 0)
			leaf = leaf->right;
		else {
			ff(leaf->data);
			leaf->data = value;
			return TRUE;
		}
	}
	ff(value);
	return FALSE;
}
