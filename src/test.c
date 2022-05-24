#include "rbt.h"

#include <stdlib.h>
#include <stdio.h>

static int intcmp(void* elem1, void* elem2)
{
	if(!elem1 || !elem2)
		return 0;
	int* int1 = (int*)elem1;
	int* int2 = (int*)elem2;
	return *int1 - *int2;
}

static void* create_int(int value) {
	int* addr;

	if(!(addr = (int*)malloc(sizeof(int))))
		return NULL;

	*addr = value;
	return (void*)addr;
}

int main()
{
	red_black_tree*	root = NULL;
	int		i = 0;

	while(i++<5000) {
		if(!add_value(&root, create_int(i), &intcmp)) {
			printf("error.\n");
			break;
		}
	}

	i = 0;
	printf("depth is:%i\n", get_tree_depth(root));
	printf("black depth is:%i\n", tree_is_valid(root));
	while(i++<1000) {
		if(!remove_value(&root, &i, &intcmp)) {
			printf("error.\n");
			break;
		}
	}

	printf("depth is:%i\n", get_tree_depth(root));
	printf("black depth is:%i\n", tree_is_valid(root));
	int key = 5;

	if(search_value(root, (void*)&key, &intcmp))
		printf("value found.\n");

	free_tree(root);
	return 0;
}
