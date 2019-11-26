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
	if (type == 12)
		ft_printf("out of memory\n");
	if (type == 13)
		ft_printf("invalid ants number\n");
	exit (type);
}

void		verbose_collecting_data(unsigned mod, char *name, int x, int y)
{
	mod == 1 ? ft_printf("ROOM: {green}[%s] {eoc}", name) :
	mod == 2 ? ft_printf("ROOM: {red}[%s] {eoc}", name) :
	ft_printf("ROOM: [%s] ", name);
	ft_printf("X: [%d], Y: [%d]\n", x, y);
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

unsigned			check_sharp(const char *line, int lc)
{
	if (*line++ == '#')
	{
		if (*line == '#')
		{
			line++;
			if (ft_strequ(line, "start"))
				return (1u);
			else if (ft_strequ(line, "end"))
				return (2u);
			else
				put_error(1, lc);
		}
		else
			ft_printf("{yellow}C: %s{eoc}\n", line);
	}
	return (0);
}

unsigned			check_several_modifiers(unsigned mod, unsigned m_flag, int lc)
{
	if (mod == 1)
	{
		if ((m_flag & 1u))
			put_error(6, lc);
		return (1u);
	}
	else if (mod == 2)
	{
		if ((m_flag & 2u))
			put_error(7, lc);
		return (2u);
	}
	else
		put_error(7, lc);
	return (0);
}

void					check_no_room_given(unsigned m_flag, int lc)
{
	if (!m_flag)
		put_error(8, lc);
	if (!(m_flag & 1u) && (m_flag & 2u))
		put_error(9, lc);
	if (m_flag & 1u && !(m_flag & 2u))
		put_error(10, lc);
}

size_t					check_ants_num(const char *line, int lc)
{
	int 	ants;
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			put_error(13, lc);
		i++;
	}
	if (!(ants = mini_atoi(line)))
		put_error(13, lc);
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
