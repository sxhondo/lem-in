#include "lem_in.h"

int					mini_atoi(const char *str)
{
	long			res;

	res = 0;
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		if (res > INT32_MAX)
			return (-1);
	}
	return ((int)res);
}

int 					only_digits(const char *str)
{
	int 				i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int							check_ants_num(const char *line, int lc)
{
	int						i;
	int 					ants;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			put_error("ants number not well formatted", lc);
		i++;
	}
	ants = mini_atoi(line);
	if (ants < 0)
		put_error("ants number not well formatted", lc);
	if (ants == 0)
		put_error("ants number cannot be 0", lc);
	return (ants);
}

void					check_no_room_given(unsigned flag, int lc)
{
	if (!flag)
		put_error("start and end rooms are not given", lc);
	if (!(flag & 1u) && (flag & 2u))
		put_error("start room is not given", lc);
	if (flag & 1u && !(flag & 2u))
		put_error("end room is not given", lc);
}

unsigned 				check_few_rooms(unsigned flag, unsigned mod, int lc)
{
	if (flag & mod)
	{
		flag == 1 ? put_error("several start rooms", lc)
			: put_error("several end rooms", lc);
	}
	return (mod);
}