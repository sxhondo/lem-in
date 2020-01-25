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

static unsigned 		get_arg(char *str)
{
	int 				i;
	int 				k;
	unsigned			flag;
	static char			*mod[5] = { "-d", "-o", "-nf", "-no", "-nl"};
	static int 			flags[5] = {P_DEBUG, P_OPEN, P_NO_FILE, 
											P_NO_OUT, P_NEW_LINE}; 
	
	flag = 0;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != ' ')
			i++;
		k = -1;	
		while (++k < 5)
		{
			if (ft_strnequ(mod[k], str, i) && i > 1)
				flag |= flags[k];
		}
		str += i;
	}
	return (flag);
}

unsigned				parse_arguments(int ac, char **arg)
{
	unsigned			flag;
	int 				i;

	flag = 0;
	if (ac == 1)
		return (0u);
	else if (ac == 2)
		flag = get_arg(arg[1]);
	else
	{
		i = 0;
		while (++i < ac)
			flag |= get_arg(arg[i]);
	}
	if (flag == 0)
	{
		ft_printf("usage: lem-in [options] < [map] \n\n"
		"options: \n\t"
		"-d --debug mode\n\t-o -- open file from an argument\n\t"
		"-nf -- don't print file\n\t-no -- don't print result output\n\t"
		"-nl -- count output result amount of new lines\n");
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
