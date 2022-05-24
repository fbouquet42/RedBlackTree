#include "stdmap.h"

#include <stdio.h>
#include <stdlib.h>

static char *rand_string(char *str, size_t size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
	if (size) {
		--size;
		for (size_t n = 0; n < size; n++) {
			int key = rand() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

void* new_value(int i) {
	int* addr;
	if(!(addr = (int*)malloc(sizeof(int))))
		printf("memory error.\n");
	if(addr)
		*addr = i;
	return (void*)addr;
}

int main()
{
	stdmap* map = new_map();

	if(!map)
		return 0;

	srand(8877886);

	int		i = 0;
	char		rand_name[20];

	while(i++ != 2) {
		rand_string(rand_name, 20);
		printf("addr:%i key:%s\n", i, rand_name);
		add_key(map, (char*)rand_name, new_value(i));
	}
	add_key(map, "felix", new_value(101));
	add_key(map, "pelix", new_value(101));
	add_key(map, "gelix", new_value(101));
	add_key(map, "nelix", new_value(101));
	add_key(map, "helix", new_value(101));
	add_key(map, "kkelix", new_value(101));
	printf("search key:%s, for value: %i\n", ".p.hsoGhgwF.hdutnna", *((int*)get_key(map, ".p.hsoGhgwF.hdutnna")));
	printf("search key:%s, for value: %i\n", rand_name, *((int*)get_key(map, rand_name)));
	printf("search key:%s, for value: %i\n", "felix", *((int*)get_key(map, "felix")));
	delete_map(map);
	return 0;
}
