#include "rbt.h"

static int recursive_check_tree(red_black_tree* leaf)
{
	if(!leaf)
		return 0;
	int left;
	int right;

	left = recursive_check_tree(leaf->left);
	right = recursive_check_tree(leaf->right);

	if(left == ERROR || right == ERROR || left != right)
		return ERROR;
	if(leaf->color == Red) {
		if(leaf->left && leaf->left->color == Red)
			return ERROR;
		else if(leaf->right && leaf->right->color == Red)
			return ERROR;
		return left;
	}
	else
		return left + 1;
}

int tree_is_valid(red_black_tree* root)
{
	if(!root)
		return 0;
	else if(root->color != Black)
		return ERROR;

	int left;
	int right;

	left = recursive_check_tree(root->left);
	right = recursive_check_tree(root->right);

	if(left == ERROR || right == ERROR || left != right)
		return FALSE;
	else
		return TRUE;
}
