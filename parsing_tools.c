#include "lem_in.h"

void		put_error(int type, int lc)
{
	if (type == 0)
		ft_printf("Can't open file\n");
	if (lc > 0)
		ft_printf("%d: {red}error: {eoc}", lc);
	if (type == 1)
		ft_printf("bad modifier\n");
	if (type == 2)
		ft_printf("bad name\n");
	if (type == 3)
		ft_printf("room or link not well formatted\n");
	if (type == 4)
		ft_printf("empty line\n");
	if (type == 5)
		ft_printf("links can't be modified as a start or end\n");
	if (type == 6 || type == 7)
		ft_printf("several %s rooms\n", type == 6 ? "start" : "end");
	if (type == 8)
		ft_printf("start and end rooms are not given\n");
	if (type == 9 || type == 10)
		ft_printf("no %s room given\n", type == 9 ? "start" : "end");
	exit (type);
}

void		verbose_collecting_data(unsigned mod, char *name, int x, int y)
{
	mod == 1 ? ft_printf("ROOM: {green}[%s] {eoc}", name) :
	mod == 2 ? ft_printf("ROOM: {red}[%s] {eoc}", name) :
	ft_printf("ROOM: [%s] ", name);
	ft_printf("X: [%d], Y: [%d]\n", x, y);
}

int			lem_atoi(const char *str, int *num, int pos, int lc)
{
	int				sign;
	long			res;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			put_error(3, lc);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error(3, lc);
	}
	num[pos] = (int)res * sign;
	return (i);
}

int 		skip_spaces(const char *str)
{
	int 	i;

	i = 0;
	while (*str && (*str == ' ' || *str == '\t'))
	{
		str++;
		i++;
	}
	return (i);
}
