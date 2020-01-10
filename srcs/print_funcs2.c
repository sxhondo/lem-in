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

void			print_all(t_structs *str)
{
	ft_printf("{cyan}ANTS: %14d\n{eoc}", str->ants_amount);
	// vertex_print((t_vertex **)&str->ver);
	// edge_print((t_edge *)str->edge);
	ways_print((t_list **)&str->ways);
	print_ants_per_paths((t_ants **)&str->ants, ft_lstlen(&str->ways) - 1);
}

void			print_void_ver(void **ver, int len)
{
	int			i;
	t_vertex	*v;

	i = 0;
	while (i < len)
	{
		v = ver[i];
		ft_printf("[%d] %s ", i, v->name);
		ft_printf("\n");
		i++;
	}
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
		ft_printf("(%d)", path_len((t_path **)&w->content) - 1);
		ft_printf("\n");
		w = w->next;
	}
	ft_printf("\n");
}

void			print_arr(int *cst, int len)
{
	int			i;

	i = 0;
	while (i < len)
	{
		if (cst[i] == INT32_MAX)
			ft_printf("-");
		else
			ft_printf("%d ", cst[i]);
		i++;
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
