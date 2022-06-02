#include "rbt.h"

#include <stdlib.h>

void tree_delete(red_black_tree* leaf, function_to_free f)
{
	if(!leaf)
		return;
	tree_delete(leaf->left, f);
	tree_delete(leaf->right, f);
	f(leaf->data);
	free(leaf);
}
