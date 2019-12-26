/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_route_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:11:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:11:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void				reset_map(t_edge **edge)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		e->cost = 0;
		e->b = 1;
		e = e->next;
	}
}

static void				put_path(t_path **route, t_edge **edge)
{
	t_path				*r;
	t_edge				*tmp;

	r = *route;
	while (r->next_p)
	{
		tmp = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		if (tmp->cost)
			tmp->cost++;
		else
			tmp->cost = 1;
		tmp->v1->vis = 0;
		tmp->v2->vis = 0;
		r = r->next_p;
	}
}

void					put_paths_on_map(t_edge **edge, t_list **ways)
{
	t_list				*w;

	w = *ways;
	reset_map(edge);
	while (w)
	{
		put_path((t_path **)&w->content, edge);
		w = w->next;
	}
	free_list(ways);
}

t_list					*add_shortest_paths(t_list **ways, t_edge **edge,
															void **ver, int len)
{
	t_path				*fn;

	while ((fn = breadth_first_search(edge, ver, len)))
	{
		if (path_len(&fn) == 2)
		{
			path_free(&fn);
			break ;
		}
		exclude_route(&fn, edge);
		add_path_to_lst(ways, fn);
	}
	free(ver);
	return (*ways);
}
