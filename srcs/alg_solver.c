/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:35:57 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:35:58 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int 			total_actions(t_list *set)
{
	t_path			*r;
	int 			tmp;

	tmp = 0;
	while (set)
	{
		r = set->content;
		tmp += path_len(&r) - 1;
		set = set->next;
	}
	return (tmp);

}

static int 			get_cf(t_list *set, int amount)
{
	int 			tmp;
	int 			len;

	len = ft_lstlen(&set);
	tmp = total_actions(set);
	tmp += amount;
	if (tmp % len)
		tmp--;
	tmp = tmp / len;
//	ft_printf("CF: %d\n", tmp);
	return (tmp);
}

static int 			find_sf(t_vertex *ver, int sf)
{

	while (ver)
	{
		if (ver->mod == sf)
			return (ver->i);
		ver = ver->next;
	}
	return (-1);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	t_path			*route;
	int 			s, f;

	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	while ((route = breadth_first_search(edge, ver, s, f, 0)))
	{
		path_print(&route, 'f');
		ft_printf("\n");
		flip_divide(&route, edge, ver);
		re_route_edges(edge, *ver);
		path_free(&route);
	}
	exit (0);
	return 0;
}