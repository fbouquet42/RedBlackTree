#include "rbt.h"

#include <stdlib.h>
#include <string.h>

static void promote_leaf(red_black_tree* leaf)
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

static red_black_tree *insert_red_leaf(red_black_tree* leaf, void* value, function_to_compare f)
{
	if(f(leaf->data, value) > 0) {
		if(!leaf->left) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return NULL;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = leaf;
			leaf->left = son;
		}
		else
			leaf = insert_red_leaf(leaf->left, value, f);
	}
	else if(f(leaf->data, value) < 0) {
		if(!leaf->right) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return NULL;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = leaf;
			leaf->right = son;
		}
		else
			leaf = insert_red_leaf(leaf->right, value, f);
	}
	else
		return NULL;

	if(!leaf->parent)
		leaf->color = Black;

	if(leaf->color == Black)
		return leaf->parent ? leaf->parent : leaf;

	//Double red check
	if((!leaf->left || !(leaf->left->color == Red)) && (!leaf->right || !(leaf->right->color == Red)))
		return leaf->parent;

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
			promote_leaf(red_son);
			promote_leaf(red_son);
			red_son->color = Black;
			return red_son;
		}
		else { //triangle
			promote_leaf(leaf);
			leaf->color = Black;
			return leaf;
		}
	}
	else {
		leaf->color = Black;
		uncle->color = Black;
		leaf->parent->color = Red;
		return leaf->parent;
	}
}

int add_value(red_black_tree** root, void* value, function_to_compare f)
{
	red_black_tree* buff;

	if(!*root) {
		if(!(buff = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return FALSE;
		memset(buff, 0, sizeof(red_black_tree));
		buff->color = Black;
		buff->data = value;
		*root = buff;
		return TRUE;
	}

	if(!(buff = insert_red_leaf(*root, value, f)))
		return FALSE;
	*root = buff;
	return TRUE;
}

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

}

static red_black_tree *find_rightmost_leaf(red_black_tree* leaf)
{
	if(!leaf->right)
		return leaf;
	else
		return find_rightmost_leaf(leaf->right);
}

static void remove_leaf(red_black_tree* leaf)
{
	if(NB_OF_CHILDREN(leaf) < 2) {
		red_black_tree* buff = NULL;
		if(leaf->left)
			buff = leaf->left;
		else if(leaf->right)
			buff = leaf->right;
		if(buff) {
			buff->parent = leaf->parent;
			buff->color = Black;
		}
		if(leaf->parent) {
			if(leaf->parent->left == leaf)
				leaf->parent->left = buff;
			else
				leaf->parent->right = buff;
		}
		free(leaf->data);
		free(leaf);
	}
	else {
		red_black_tree* inorder_predecessor = find_rightmost_leaf(leaf->left);
		swap_leaves(leaf, inorder_predecessor);
		remove_leaf(leaf);
	}
}

static red_black_tree *recursive_remove_value(red_black_tree* leaf, void* value, function_to_compare f)
{

	if(!leaf)
		return NULL;
	if(f(leaf->data, value) > 0) {
		leaf = recursive_remove_value(leaf->left, value, f);
	}
	else if(f(leaf->data, value) < 0) {
		leaf = recursive_remove_value(leaf->right, value, f);
	}
	else {
		remove_leaf(leaf);
	}
	return NULL;
}

int remove_value(red_black_tree** root, void* value, function_to_compare f)
{
	red_black_tree* buff;

	if(!*root)
		return FALSE;

	if(!(buff = recursive_remove_value(*root, value, f)))
		return FALSE;

	*root = buff;
	return TRUE;
}

red_black_tree *search_value(red_black_tree* leaf, void* value, function_to_compare f)
{
	if(!leaf)
		return NULL;
	if(f(leaf->data, value) > 0) {
		return search_value(leaf->left, value, f);
	}
	else if(f(leaf->data, value) < 0) {
		return search_value(leaf->right, value, f);
	}
	else
		return leaf;
}

void free_tree(red_black_tree* leaf)
{
	if(!leaf)
		return ;
	free_tree(leaf->left);
	free_tree(leaf->right);
	free(leaf->data);
	free(leaf);
}
