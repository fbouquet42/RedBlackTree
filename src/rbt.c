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

	red_black_tree* uncle = UNCLE(leaf);

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

red_black_tree *add_value(red_black_tree* root, void* value, function_to_compare f)
{
	red_black_tree* son;

	if(!root) {
		if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return NULL;
		memset(son, 0, sizeof(red_black_tree));
		son->color = Black;
		son->data = value;
		return son;
	}

	return insert_red_leaf(root, value, f);
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
