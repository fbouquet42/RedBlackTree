#include "rbt.h"

void leaf_promote(red_black_tree* leaf)
{
	red_black_tree* parent = leaf->parent;
	red_black_tree* buff;

	if(!parent)
		return ;

	//grandparent
	leaf->parent = parent->parent;
	if(parent->parent) {
		if(parent->parent->left == parent)
			parent->parent->left = leaf;
		else
			parent->parent->right = leaf;
	}
	//parent
	parent->parent = leaf;
	if(parent->left == leaf) {
		buff = leaf->right;

		leaf->right = parent;
		parent->left = buff;
	}
	else {
		buff = leaf->left;

		leaf->left = parent;
		parent->right = buff;
	}

	if(buff)
		buff->parent = parent;
}
