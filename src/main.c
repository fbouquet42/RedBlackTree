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
	while(i++<22000)
		uint_map_add(map, rand_string(tab, 20), 19);

	uint_map_delete(map);
	return 0;
}
