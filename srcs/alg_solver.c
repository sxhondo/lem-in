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

#include <stdio.h>
#include "lem_in.h"

static t_list		*mini_solution(t_path *route, t_list **ways, void **vp)
{
	add_path_to_lst(ways, route);
	free(vp);
	return (*ways);
}

static void			set_indexes_of_ver(t_edge **edge, void **ver, int len)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		e->v1_i = get_index_of_ver(ver, e->v1->name, len);
		e->v1->i = e->v1_i;
		e->v2_i = get_index_of_ver(ver, e->v2->name, len);
		e->v2->i = e->v2_i;
		e = e->next;
	}
}

static int 			get_cf(t_list **ways, t_path *route, int ants)
{
	int 			steps;
	int 			paths;
	int 			tmp;
	t_list			*l;

	paths = ft_lstlen(ways) ? ft_lstlen(ways) : 1;
	steps = 0;
	l = *ways;
	if (l)
	{
		while (l)
		{
			steps += path_len((t_path **)&l->content) - 1;
			l = l->next;
		}
		steps += path_len(&route) - 1;
	}
	else
		steps = path_len(&route) - 1;
	tmp = steps + ants;
	return (tmp % paths ? (tmp / paths) : (tmp / paths) - 1);

}

static t_list		*get_cross_set(t_edge **edge, void **vp, int len, int ants)
{
	t_path			*route;
	t_list			*ways;

	ways = NULL;
	while ((route = get_cheapest_path(edge, vp, len)))
	{
		exclude_route(&route, edge);
		cross_paths(route, &ways);
		add_path_to_lst(&ways, route);
	}
	reset_map(edge, 0);
	put_paths_on_map(edge, &ways);
	while ((route = breadth_first_search(edge, vp, len)))
	{
		delete_route(&route, edge);
		if (!(cross_paths(route, &ways)))
			add_path_to_lst(&ways, route);
	}
	return (ways);
}

static t_list		*get_brute_set(t_edge **edge, void **vp, int len)
{
	t_path			*route;
	t_list			*ways;

	ways = NULL;
	reset_map(edge, 1);
	while ((route = breadth_first_search(edge, vp, len)))
	{
		delete_route(&route, edge);
		if (!(cross_paths(route, &ways)))
			add_path_to_lst(&ways, route);
	}
	return (ways);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	void			**vp;
	int				len;
	t_list			*set_1;
	t_list			*set_2;
	t_path			*route;

	set_1 = NULL;
	len = vertex_len(ver);
	vp = convert_ver_to_ptrs(ver, len);
	set_indexes_of_ver(edge, vp, len);
	if (!(route = get_cheapest_path(edge, vp, len)))
		put_error("no possible solution", 0);
	if (path_len(&route) == 2)
		return (mini_solution(route, &set_1, vp));
	path_free(&route);
	set_1 = get_cross_set(edge, vp, len, ants);
	// return (set_1);

	set_2 = get_brute_set(edge, vp, len);
	free(vp);
	if (ft_lstlen(&set_1) > ft_lstlen(&set_2))
	{
		free_list(&set_2);
		return (set_1);
	}
	else
	{
		free_list(&set_1);
		return (set_2);
	}
}
