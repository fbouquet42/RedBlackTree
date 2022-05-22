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

	while(i++<10000)
		if(!add_value(&root, create_int(i), &intcmp)) {
			printf("error.\n");
			break;
		}

	int key = 5555;

	if(search_value(root, (void*)&key, &intcmp))
		printf("value found.\n");
	free_tree(root);
	return 0;
}
