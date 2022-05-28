#ifndef RBT_H
# define RBT_H

/*
 * MACROS
 */

# define LEAF_ADDED 2
# define LEAF_REPLACED 1

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SIBLING(x) (x->parent->left == x) ? x->parent->right : x->parent->left
# define NB_OF_CHILDREN(x) ((int)(x->left != NULL) + (int)(x->right != NULL))
# define HAS_RED_CHILD(x) (x->left ? x->left->color == Red : FALSE) || (x->right ? x->right->color == Red : FALSE)
# define TRIANGLE(x, y, z) (x->left == y && y->left != z) || (x->right == y && y->right != z)

/*
 * TYPES
 */

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

/*
 * API
 */

/* api function: return the leaf equal to the value if it exists*/
red_black_tree*	tree_get_leaf(red_black_tree* leaf, const void* value, function_to_compare f);

/* api function: free the memory's tree*/
void		tree_delete(red_black_tree* leaf, function_to_free f);

/* api function: add new leaf, return false if leaf already exists or if memory fails*/
int		tree_add(red_black_tree** root, void* value,  function_to_compare fc, function_to_free ff);

/* api function: replace existing leaf, return false if leaf doesnt exist or if memory fails*/
int		tree_replace(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff);

/* api function: emplace leaf, replace if leaf already exists otherwise create a new leaf, return false if memory fails*/
int		tree_emplace(red_black_tree** root, void* value, function_to_compare fc, function_to_free ff);

/* api function: remove leaf, return false if leaf doesnt exist*/
int		tree_remove(red_black_tree** root, const void* value, function_to_compare fc, function_to_free ff);

/*
 * UTILS
 */

/* utils function: rotate the leaf in direction of its parent*/
void leaf_promote(red_black_tree* leaf);

/* utils function: resolve double red when adding new leaf*/
red_black_tree *tree_resolve_double_red(red_black_tree* leaf);

/*
 * TEST
 */

/* test function: check the black depth, the black root and the red children properties*/
int 		tree_is_valid(red_black_tree* leaf);

/* test function: return the depth of the tree*/
int		tree_get_depth(red_black_tree* leaf);

#endif //RBT_H
