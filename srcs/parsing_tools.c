#include "lem_in.h"

int 			skip_spaces(const char *str)
{
	int 		i;

	i = 0;
	while (*str && (*str == ' ' || *str == '\t'))
	{
		str++;
		i++;
	}
	return (i);
}


int						cut_after_symbol(const char *src, char **dst, char sym)
{
	int 				i;

	i = 0;
	while (src[i] && src[i] != sym)
		i++;
	if (!(*dst = ft_strndup(src, i)))
	{
		ft_strdel(dst);
		put_error("cannot allocate memory", 0);
	}
	return (i);
}

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
		put_error("bad modifier", lc);
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			put_error("bad modifier", lc);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error("overflow value in modifier", lc);
	}
	num[pos] = (int)res * sign;
	return (i);
}