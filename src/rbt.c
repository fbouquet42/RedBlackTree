#include "rbt.h"

#include <stdlib.h>
#include <string.h>

//if parent is red ?

static void promote_node(red_black_tree* to_promote)
{
	red_black_tree* parent = to_promote->parent;
	red_black_tree* buff;

	if(!parent)
		return ;

	//grandparent
	to_promote->parent = parent->parent;
	if(parent->parent) {
		if(parent->parent->left == parent)
			parent->parent->left = to_promote;
		else
			parent->parent->right = to_promote;
	}
	//parent
	parent->parent = to_promote;
	if(parent->left == to_promote) {
		buff = to_promote->right;

		to_promote->right = parent;
		parent->left = buff;
	}
	else {
		buff = to_promote->left;

		to_promote->left = parent;
		parent->right = buff;
	}

	if(buff)
		buff->parent = parent;
}

static red_black_tree *insert_red_element(red_black_tree* element, void* value, function_to_compare f)
{
	if(f(element->data, value) > 0) {
		if(!element->left) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return NULL;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = element;
			element->left = son;
		}
		else
			element = insert_red_element(element->left, value, f);
	}
	else if(f(element->data, value) < 0) {
		if(!element->right) {
			red_black_tree* son;
			if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
				return NULL;
			memset(son, 0, sizeof(red_black_tree));
			son->color = Red;
			son->data = value;
			son->parent = element;
			element->right = son;
		}
		else
			element = insert_red_element(element->right, value, f);
	}

	if(!element->parent)
		element->color = Black;

	if(element->color == Black)
		return element->parent ? element->parent : element;

	//Double red check
	if((!element->left || !(element->left->color == Red)) && (!element->right || !(element->left->color == Red)))
		return element->parent;

	red_black_tree* uncle = UNCLE(element);

	if(!uncle || uncle->color == Black) {
		red_black_tree* red_son;
		if(!element->left)
			red_son = element->right;
		else
			red_son = (element->left->color == Red) ? element->left : element->right;

		red_black_tree* parent = element->parent;
		parent->color = Red;

		if(TRIANGLE(parent, element, red_son)) { //triangle
			promote_node(red_son);
			promote_node(red_son);
			red_son->color = Black;
			return red_son;
		}
		else { //triangle
			promote_node(element);
			element->color = Black;
			return element;
		}
	}
	else {
		element->color = Black;
		uncle->color = Black;
		element->parent->color = Red;
		return element->parent;
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

	return insert_red_element(root, value, f);
}
