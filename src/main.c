#include "rbt.h"

#include <stdlib.h>

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
	red_black_tree *root = NULL;

	root = add_value(root, create_int(0), &intcmp);
	root = add_value(root, create_int(1), &intcmp);
	root = add_value(root, create_int(2), &intcmp);
	root = add_value(root, create_int(3), &intcmp);
	root = add_value(root, create_int(4), &intcmp);
	root = add_value(root, create_int(5), &intcmp);
	return 0;
}
