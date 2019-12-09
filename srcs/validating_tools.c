 #include "incs/lem_in.h"

 int					lem_atoi(const char *str, int *num, int pos, int lc)
{
	int				sign;
	long			res;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		put_error(3, lc, NULL);
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			put_error(3, lc, NULL);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error(3, lc, NULL);
	}
	num[pos] = (int)res * sign;
	return (i);
}

int					mini_atoi(const char *str)
{
	int				sign;
	long			res;

	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+'))
		sign = *str++ == '-' ? -1 : 1;
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			return (0);
	}
	return ((int)res * sign);
}

size_t					check_ants_num(const char *line, int lc)
{
	int 	ants;
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			put_error(13, lc, NULL);
		i++;
	}
	if (!(ants = mini_atoi(line)))
		put_error(14, lc, NULL);
	return (ants);
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
