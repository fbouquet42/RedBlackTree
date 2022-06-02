#include "rbt.h"

red_black_tree *tree_resolve_double_red(red_black_tree* leaf)
{

	if(!leaf->parent) {
		leaf->color = Black;
		return leaf;
	}

	if(leaf->color == Black)
		return tree_resolve_double_red(leaf->parent);

	//Double red check
	if((!leaf->left || !(leaf->left->color == Red)) && (!leaf->right || !(leaf->right->color == Red)))
		return tree_resolve_double_red(leaf->parent);

	red_black_tree* uncle = SIBLING(leaf);

	if(!uncle || uncle->color == Black) {
		red_black_tree* red_son;
		if(!leaf->left)
			red_son = leaf->right;
		else
			red_son = (leaf->left->color == Red) ? leaf->left : leaf->right;

		red_black_tree* parent = leaf->parent;
		parent->color = Red;

		if(TRIANGLE(parent, leaf, red_son)) { //triangle
			leaf_promote(red_son);
			leaf_promote(red_son);
			red_son->color = Black;
			return tree_resolve_double_red(red_son);
		}
		else { //line
			leaf_promote(leaf);
			leaf->color = Black;
			return tree_resolve_double_red(leaf);
		}
	}
	else {
		leaf->color = Black;
		uncle->color = Black;
		leaf->parent->color = Red;
		return tree_resolve_double_red(leaf->parent);
	}
}
