#ifndef RBT_H
# define RBT_H

# define UNCLE(x) (x->parent->left == x) ? x->parent->right : x->parent->left
# define TRIANGLE(x, y, z) (x->left == y && y->left != z) || (x->right == y && y->right != z)

typedef struct s_rbt
{
	void*			data;
	struct s_rbt*		parent;
	struct s_rbt*		left;
	struct s_rbt*		right;
	enum {Red, Black}	color;
}				red_black_tree;

typedef int (*function_to_compare)(void* elem1, void* elem2);

red_black_tree* add_value(red_black_tree* root, void* value, function_to_compare f);
red_black_tree*	search_value(red_black_tree* leaf, void* value, function_to_compare f);
void		free_tree(red_black_tree* leaf);

#endif //RBT_H
