#include "uint_map.h"

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


int main()
{
	stdmap*	map = uint_map_new();

	srand(87463109);

	int i = 0;
	char tab[20];
	while(i++<22)
		uint_map_add(map, rand_string(tab, 20), 19);

	stdmap* map2 = uint_map_copy(map);

	//uint_map_join(map, map2);

	stdmap_it* it = it_first(map);
	while(it_is_valid(it)) {
		printf("%s\n", it_get_key(it));
		it_next(it);
	}
	printf("\n");
	stdmap_it* it2 = it_first(map2);
	while(it_is_valid(it2)) {
		printf("%s\n", it_get_key(it2));
		it_next(it2);
	}
	printf("map2 size:%i\n", uint_map_get_size(map2));

	uint_map_delete(map);
	uint_map_delete(map2);
	return 0;
}
