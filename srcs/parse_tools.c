/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:14:34 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:14:35 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						skip_spaces(const char *str)
{
	int					i;

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
	int					i;

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

int						lem_atoi(const char *str, int *num, int pos, int lc)
{
	int					sign;
	long				res;
	int					i;

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

unsigned				parse_arguments(int ac, char **arg)
{
	unsigned			flag;
	int					i;

	flag = 0;
	i = 1;
	while (i < ac)
	{
		if (ft_strequ(arg[i], "-c"))
			flag |= COLORS;
		if (ft_strequ(arg[i], "-d"))
			flag |= DEBUG;
		if (ft_strequ(arg[i], "-o"))
			flag |= OPEN;
		if (ft_strequ(arg[i], "-nofile"))
			flag |= NO_FILE;
		if (ft_strequ(arg[i], "-noout"))
			flag |= NO_OUT;
		i++;
	}
	return (flag);
}

int						parse_room_name(const char *line, char **name, int lc)
{
	const char			*start;
	int					i;

	start = line;
	line += skip_spaces(line);
	if (*line == 'L')
		put_error("room name cannot starts with 'L'", lc);
	i = cut_after_symbol(line, name, ' ');
	line += i;
	line += skip_spaces(line);
	return ((int)(line - start));
}
