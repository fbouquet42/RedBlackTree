#include "rbt.h"

#include <stdlib.h>
#include <string.h>

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

int get_tree_depth(red_black_tree* leaf)
{
	if(!leaf)
		return 0;
	int left;
	int right;

	left = get_tree_depth(leaf->left);
	right = get_tree_depth(leaf->right);

	return (left > right) ? left + 1 : right + 1;
}

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

static red_black_tree *resolve_tree(red_black_tree* leaf)
{

	if(!leaf->parent) {
		leaf->color = Black;
		return leaf;
	}

	if(leaf->color == Black)
		return resolve_tree(leaf->parent);

	//Double red check
	if((!leaf->left || !(leaf->left->color == Red)) && (!leaf->right || !(leaf->right->color == Red)))
		return resolve_tree(leaf->parent);

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
			return resolve_tree(red_son);
		}
		else { //triangle
			promote_leaf(leaf);
			leaf->color = Black;
			return resolve_tree(leaf);
		}
	}
	else {
		leaf->color = Black;
		uncle->color = Black;
		leaf->parent->color = Red;
		return resolve_tree(leaf->parent);
	}
}

int emplace_value(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;

	if(!*root) {
		if(!(leaf = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return FALSE;
		memset(leaf, 0, sizeof(red_black_tree));
		leaf->color = Black;
		leaf->data = value;
		*root = leaf;
		return TRUE;
	}

	leaf = *root;
	while(leaf) {
		if(fc(leaf->data, value) > 0) {
			if(!leaf->left) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->left = son;
				break;
			}
			else
				leaf = leaf->left;
		}
		else if(fc(leaf->data, value) < 0) {
			if(!leaf->right) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->right = son;
				break;
			}
			else
				leaf = leaf->right;
		}
		else {
			ff(leaf->data);
			leaf->data = value;
			return LEAF_REPLACED;
		}
	}

	*root = resolve_tree(leaf);

	return LEAF_ADDED;
}

int replace_value(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff)
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

int add_value(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;

	if(!*root) {
		if(!(leaf = (red_black_tree*)malloc(sizeof(red_black_tree))))
			return FALSE;
		memset(leaf, 0, sizeof(red_black_tree));
		leaf->color = Black;
		leaf->data = value;
		*root = leaf;
		return TRUE;
	}

	leaf = *root;
	while(leaf) {
		if(fc(leaf->data, value) > 0) {
			if(!leaf->left) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->left = son;
				break;
			}
			else
				leaf = leaf->left;
		}
		else if(fc(leaf->data, value) < 0) {
			if(!leaf->right) {
				red_black_tree* son;
				if(!(son = (red_black_tree*)malloc(sizeof(red_black_tree))))
					return FALSE;
				memset(son, 0, sizeof(red_black_tree));
				son->color = Red;
				son->data = value;
				son->parent = leaf;
				leaf->right = son;
				break;
			}
			else
				leaf = leaf->right;
		}
		else {
			ff(value);
			return FALSE;
		}
	}

	*root = resolve_tree(leaf);

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

static void resolve_double_black(red_black_tree* parent, red_black_tree* leaf)
{
	red_black_tree* sibling = (parent->left == leaf) ? parent->right : parent->left;

	if(sibling->color == Red) {
		parent->color = Red;
		sibling->color = Black;
		promote_leaf(sibling);
		resolve_double_black(parent, leaf);
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
				promote_leaf(triangulated_son);
				triangulated_son->color = Black;
				sibling->color = Red;
				sibling = triangulated_son;
			}

			promote_leaf(sibling);
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
				resolve_double_black(parent->parent, parent);
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
				resolve_double_black(leaf->parent, NULL);
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

red_black_tree* search_leaf(red_black_tree* leaf, const void* value, function_to_compare f)
{
	while(leaf) {
		if(f(leaf->data, value) > 0)
			leaf = leaf->left;
		else if(f(leaf->data, value) < 0)
			leaf = leaf->right;
		else
			break;
	}
	return leaf;
}

int remove_value(red_black_tree** root, const void* value, function_to_compare fc, function_to_free ff)
{
	red_black_tree* leaf;

	if(!*root)
		return FALSE;

	if(!(leaf = search_leaf(*root, value, fc)))
		return FALSE;

	red_black_tree* child = (*root)->left ? (*root)->left : (*root)->right;

	remove_leaf(leaf, ff);

	if(leaf == *root)
		*root = get_root(child);
	else
		*root = get_root(*root);

	return TRUE;
}

void free_tree(red_black_tree* leaf, function_to_free f)
{
	if(!leaf)
		return;
	free_tree(leaf->left, f);
	free_tree(leaf->right, f);
	f(leaf->data);
	free(leaf);
}
