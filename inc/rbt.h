#ifndef RBT_H
# define RBT_H

typedef struct s_rbt
{
	void*		data;
	struct s_rbt*	left;
	struct s_rbt*	right;
	enum {Red, Black, DoubleBlack} color;
} red_black_tree;

#endif
