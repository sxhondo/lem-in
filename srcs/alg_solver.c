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

static t_list		*find_overlapping_routes(t_edge **edge, void **vp,
											int len, int ants)
{
	t_path			*route;
	t_list			*ways;

	ways = NULL;
	while ((route = get_cheapest_path(edge, vp, len)))
	{
		exclude_route(&route, edge);
		add_path_to_lst(&ways, route);
		if (ants == 1)
			break ;
	}
	return (ways);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	void			**vp;
	int				len;
	t_list			*ways;
	t_path			*route;

	ways = NULL;
	len = vertex_len(ver);
	vp = convert_ver_to_ptrs(ver, len);
	set_indexes_of_ver(edge, vp, len);
	if (!(route = get_cheapest_path(edge, vp, len)))
		put_error("no possible solution", 0);
	if (path_len(&route) == 2)
		return (mini_solution(route, &ways, vp));
	path_free(&route);
	ways = find_overlapping_routes(edge, vp, len, ants);
	put_paths_on_map(edge, &ways);
	return (add_shortest_paths(&ways, edge, vp, len));
}
