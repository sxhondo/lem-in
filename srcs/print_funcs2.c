/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:56:11 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:56:12 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			count_print_nl(t_vec *vec)
{
	char		*str;
	unsigned	i;
	int			c;

	i = 0;
	c = 0;
	str = vec->data;
	while (i < vec->total)
	{
		if (str[i] == '\n')
			c++;
		i++;
	}
	ft_printf("\nNL: %d\n", c);
}

void			print_all(t_structs *str)
{
	ft_printf("\n{cyan}ANTS: %14d\n{eoc}", str->ants_amount);
	ways_print((t_list **)&str->ways);
}

void			ways_print(t_list **ways)
{
	int			i;
	t_list		*w;

	i = 0;
	w = *ways;
	while (w)
	{
		ft_printf("[%d] ", i++);
		path_print((t_path **)&w->content, 'f');
		ft_printf("(%d)", path_len((t_path *)w->content));
		ft_printf("\n");
		w = w->next;
	}
	ft_printf("\n");
}

void			put_error(char *err, int lc)
{
	lc ? ft_fprintf(2, "%d: {red}error: {eoc}", lc) :
		ft_fprintf(2, "{red}error: {eoc}");
	ft_fprintf(2, "%s\n", err);
	exit(1);
}
