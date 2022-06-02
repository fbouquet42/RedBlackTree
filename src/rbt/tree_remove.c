#include "rbt.h"

#include <stdlib.h>

static void swap_leaves(red_black_tree* leaf1, red_black_tree* leaf2)
{
	//buffers
	red_black_tree* leaf1_parent = leaf1->parent;
	red_black_tree* leaf1_left = leaf1->left;
	red_black_tree* leaf1_right = leaf1->right;

	leaf1->parent = leaf2->parent == leaf1 ? leaf2 : leaf2->parent;
	leaf1->left = leaf2->left == leaf1 ? leaf2 : leaf2->left;
	leaf1->right = leaf2->right == leaf1 ? leaf2 : leaf2->right;
	if(leaf2->parent && leaf2->parent != leaf1) {
		if(leaf2->parent->left == leaf2)
			leaf2->parent->left = leaf1;
		else
			leaf2->parent->right = leaf1;
	}
	if(leaf2->left && leaf2->left != leaf1)
		leaf2->left->parent = leaf1;
	if(leaf2->right && leaf2->right != leaf1)
		leaf2->right->parent = leaf1;

	leaf2->parent = leaf1_parent == leaf2 ? leaf1 : leaf1_parent;
	leaf2->left = leaf1_left == leaf2 ? leaf1 : leaf1_left;
	leaf2->right = leaf1_right == leaf2 ? leaf1 : leaf1_right;
	if(leaf1_parent && leaf1_parent != leaf2) {
		if(leaf1_parent->left == leaf1)
			leaf1_parent->left = leaf2;
		else
			leaf1_parent->right = leaf2;
	}
	if(leaf1_left && leaf1_left != leaf2)
		leaf1_left->parent = leaf2;
	if(leaf1_right && leaf1_right != leaf2)
		leaf1_right->parent = leaf2;

	if(leaf1->color == Red) {
		leaf1->color = leaf2->color;
		leaf2->color = Red;
	}
	else {
		leaf1->color = leaf2->color;
		leaf2->color = Black;
	}

}

static red_black_tree *find_rightmost_leaf(red_black_tree* leaf)
{
	if(!leaf->right)
		return leaf;
	else
		return find_rightmost_leaf(leaf->right);
}

static void tree_resolve_double_black(red_black_tree* parent, red_black_tree* leaf)
{
	red_black_tree* sibling = (parent->left == leaf) ? parent->right : parent->left;

	if(sibling->color == Red) {
		parent->color = Red;
		sibling->color = Black;
		leaf_promote(sibling);
		tree_resolve_double_black(parent, leaf);
	}
	else {
		if(HAS_RED_CHILD(sibling)) {
			red_black_tree* triangulated_son = NULL;

			if(parent->left == sibling) {
				if(!sibling->left || sibling->left->color != Red)
					triangulated_son = sibling->right;
			}
			else {
				if(!sibling->right || sibling->right->color != Red)
					triangulated_son = sibling->left;
			}
			if(triangulated_son) {
				leaf_promote(triangulated_son);
				triangulated_son->color = Black;
				sibling->color = Red;
				sibling = triangulated_son;
			}

			leaf_promote(sibling);
			sibling->color = parent->color;
			sibling->left->color = Black;
			sibling->right->color = Black;
		}
		else {
			sibling->color = Red;
			if(!parent->parent)
				return;
			if(parent->color == Red)
				parent->color = Black;
			else
				tree_resolve_double_black(parent->parent, parent);
		}
	}
}

static void remove_leaf(red_black_tree* leaf, function_to_free f)
{
	if(NB_OF_CHILDREN(leaf) < 2) {
		red_black_tree* branch = NULL;
		if(leaf->left)
			branch = leaf->left;
		else if(leaf->right)
			branch = leaf->right;
		if(branch) {
			branch->parent = leaf->parent;
			branch->color = Black;
		}
		if(leaf->parent) {
			if(leaf->parent->left == leaf)
				leaf->parent->left = branch;
			else
				leaf->parent->right = branch;
			if(!branch && leaf->color == Black)
				tree_resolve_double_black(leaf->parent, NULL);
		}
		f(leaf->data);
		free(leaf);
	}
	else {
		red_black_tree* inorder_predecessor = find_rightmost_leaf(leaf->left);
		swap_leaves(leaf, inorder_predecessor);
		remove_leaf(leaf, f);
	}
}

static red_black_tree* get_root(red_black_tree* leaf)
{
	while(leaf) {
		if(!leaf->parent)
			break;
		leaf = leaf->parent;
	}
	return leaf;
}

int tree_remove(red_black_tree** root, const void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;

	if(!*root)
		return FALSE;

	if(!(leaf = tree_get_leaf(*root, value, fc)))
		return FALSE;

	red_black_tree* child = (*root)->left ? (*root)->left : (*root)->right;

	remove_leaf(leaf, ff);

	if(leaf == *root)
		*root = get_root(child);
	else
		*root = get_root(*root);

	return TRUE;
}
