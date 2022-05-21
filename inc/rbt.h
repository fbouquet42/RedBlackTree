#ifndef RBT_H
# define RBT_H

# define TRUE 1
# define FALSE 0

typedef struct s_rbt
{
	void*			data;
	struct s_rbt*		parent;
	struct s_rbt*		left;
	struct s_rbt*		right;
	enum {Red, Black}	color;
}				red_black_tree;

typedef int (*function_to_compare)(void* elem1, void* elem2);

red_black_tree *add_value(red_black_tree* root, void* value, function_to_compare f);

#endif
