#include "rbt.h"

int tree_get_depth(red_black_tree* leaf)
{
	if(!leaf)
		return 0;
	int left;
	int right;

	left = tree_get_depth(leaf->left);
	right = tree_get_depth(leaf->right);

	return (left > right) ? left + 1 : right + 1;
}
