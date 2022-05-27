#ifndef RBT_H
# define RBT_H

# define LEAF_ADDED 2
# define LEAF_REPLACED 1

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SIBLING(x) (x->parent->left == x) ? x->parent->right : x->parent->left
# define NB_OF_CHILDREN(x) ((int)(x->left != NULL) + (int)(x->right != NULL))
# define HAS_RED_CHILD(x) (x->left ? x->left->color == Red : FALSE) || (x->right ? x->right->color == Red : FALSE)
# define TRIANGLE(x, y, z) (x->left == y && y->left != z) || (x->right == y && y->right != z)

typedef struct s_rbt
{
	void*			data;
	struct s_rbt*		parent;
	struct s_rbt*		left;
	struct s_rbt*		right;
	enum {Red, Black}       color;
}				red_black_tree;

typedef int (*function_to_compare)(const void* elem1, const void* elem2);
typedef void (*function_to_free)(void* elem);

int 		tree_is_valid(red_black_tree* leaf);
int		add_value(red_black_tree** root, void* value,  function_to_compare fc, function_to_free ff);
int		replace_value(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff);
int		emplace_value(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff);
int		remove_value(red_black_tree** root, const void* value, function_to_compare fc, function_to_free ff);
red_black_tree*	search_leaf(red_black_tree* leaf, const void* value, function_to_compare f);
int		get_tree_depth(red_black_tree* leaf);
void		free_tree(red_black_tree* leaf, function_to_free f);

#endif //RBT_H
