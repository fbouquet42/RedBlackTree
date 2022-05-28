#include "string_map.h"

#include <stdlib.h>
#include <string.h>

static void* copy_string(void* string)
{
	char*	new_string;
	int	len;

	len = strlen((const char*)string);
	if(!(new_string = (char*)malloc(sizeof(char) * (len + 1))))
		return NULL;
	strcpy(new_string, (const char*)string);
	new_string[len] = '\0';
	return (void*)new_string;
}

int string_map_add(stdmap* map, const char* key, char* val)
{
	void*	cpy;
	if(!(cpy = copy_string(&val)))
		return 0;
	return map_add(map, key, cpy);
}

int string_map_replace(stdmap* map, const char* key, char* val)
{
	void*	cpy;
	if(!(cpy = copy_string(val)))
		return 0;
	return map_replace(map, key, cpy);
}

stdmap*	string_map_new()
{
	return map_new(&pair_delete, &copy_string);
}

char* string_map_get_value(const stdmap* map, const char* key)
{
	return (char*)map_get_value(map, key);
}
