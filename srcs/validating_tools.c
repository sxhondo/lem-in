 #include "incs/lem_in.h"

 int			*init_tab(int size, int c)
 {
	 int 	*tab;

	 if (!(tab = ft_new_array(size, c)))
		 return (0);
	 tab[0] = 0;
	 return (tab);
 }

void					**new_ptr_array(int size)
{
	int 				i;
	void				**tab;

	if (!(tab = (void **)malloc(sizeof(void *) * size)) || size <= 0)
	{
		put_error(12, 0, NULL);
		return (NULL);
	}
	i = -1;
	while (++i < size)
		tab[i] = NULL;
	return (tab);
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
				put_error(1, lc, NULL);
		}
		else
			ft_printf("{yellow}C: %s{eoc}\n", line);
	}
	return (0);
}

unsigned			check_few_mod(unsigned mod, unsigned m_flag, int lc)
{
	if (mod == 1)
	{
		if ((m_flag & 1u))
			put_error(6, lc, NULL);
		return (1u);
	}
	else if (mod == 2)
	{
		if ((m_flag & 2u))
			put_error(7, lc, NULL);
		return (2u);
	}
	else
		put_error(7, lc, NULL);
	return (0);
}

void					check_no_room_given(unsigned m_flag, int lc)
{
	if (!m_flag)
		put_error(8, lc, NULL);
	if (!(m_flag & 1u) && (m_flag & 2u))
		put_error(9, lc, NULL);
	if (m_flag & 1u && !(m_flag & 2u))
		put_error(10, lc, NULL);
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
