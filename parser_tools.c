#include "lem_in.h"

int 		skip_spaces(const char *str)
{
	int 	i;

	i = 0;
	while (*str && *str++ == ' ')
		i++;
	return (i);
}
