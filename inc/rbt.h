#ifndef RBT_H
# define RBT_H

# define TRUE 1
# define FALSE 0

# define SIBLING(x) (x->parent->left == x) ? x->parent->right : x->parent->left
# define NB_OF_CHILDREN(x) ((int)(x->left != NULL) + (int)(x->right != NULL))
# define COLOR_OF_CHILD(x) (x->left ? x->left->color : (x->right ? x->right->color : Black))
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

int		add_value(red_black_tree** root, void* value, function_to_compare f);
int		remove_value(red_black_tree** root, void* value, function_to_compare f);
red_black_tree*	search_value(red_black_tree* leaf, void* value, function_to_compare f);
void		free_tree(red_black_tree* leaf);

#endif //RBT_H
