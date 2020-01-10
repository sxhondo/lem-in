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
			tmp->cost = 0;
		else
			tmp->cost = 1;
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

static void			delete_route(t_path **route, t_edge **edge)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->cost = 0;
		if (e->v1->mod == 0)
			e->v1->vis = 1;
		r = r->next_p;
	}
}

int 					cross_paths(t_path *fn, t_list **ways)
{
	t_list 				*l;
	t_path 				*tmp;

	while (fn)
	{
		l = *ways;
		while (l)
		{
			tmp = l->content;
			while (tmp)
			{
				if (ft_strequ(fn->curr_v->name, tmp->curr_v->name) &&
					fn->curr_v->mod == 0)
					return (1);
				tmp = tmp->next_p;
			}
			l = l->next;
		}
		fn = fn->next_p;
	}
	return (0);
}

t_list					*add_shortest_paths(t_list **ways, t_edge **edge,
															void **ver, int len)
{
	t_path				*fn;

	while ((fn = breadth_first_search(edge, ver, len)))
	{
		delete_route(&fn, edge);
		if (!cross_paths(fn, ways))
			add_path_to_lst(ways, fn);
	}
	free(ver);
	return (*ways);
}
