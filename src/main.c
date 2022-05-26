#include "stdmap.h"
#include "rbt.h"

#include <stdio.h>
#include <stdlib.h>

static char *rand_string(char *str, size_t size)
{
	const char charset[] = "0123456789.";
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

	while(i++ != 220) {
		rand_string(rand_name, 20);
		printf("addr:%i key:%s\n", i, rand_name);
		map_add_key(map, (char*)rand_name, new_value(i));
	}

	printf("istree valid:%i\n", map_is_valid(map));

	map_add_key(map, "felix", new_value(101));
	map_add_key(map, "pelix", new_value(101));
	map_add_key(map, "gelix", new_value(101));
	map_add_key(map, "nelix", new_value(101));
	map_add_key(map, "helix", new_value(101));
	map_add_key(map, "kkelix", new_value(101));

	printf("istree valid:%i\n", map_is_valid(map));



	printf("search key:%s, for value: %i\n", rand_name, *((int*)map_get_key(map, rand_name)));
	printf("search key:%s, for value: %i\n", "felix", *((int*)map_get_key(map, "felix")));
	map_remove_key(map, "felix");
	printf("all good.\n");
	printf("search key:%s, for value: %i\n", rand_name, *((int*)map_get_key(map, rand_name)));


	stdmap_it* it = it_first(map);
	while(it_is_valid(it))
	{
		printf("%s\n", it_get_key(it));
		it_next(it);
	}
	printf("\n");
	it = it_last(map);
	while(it_is_valid(it))
	{
		printf("%s\n", it_get_key(it));
		it_previous(it);
	}
	printf("istree valid:%i\n", map_is_valid(map));
	delete_map(map);
	return 0;
}
