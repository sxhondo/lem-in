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

void					reset_map(t_edge **edge, int c)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		e->cost = c;
		e->b = 1;
		e->v1->vis = 0;
		e->v2->vis = 0;
		e = e->next;
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
				if (ft_strequ(fn->curr_v->name, tmp->curr_v->name)
						&& fn->curr_v->mod == 0)
					return (1);
				tmp = tmp->next_p;
			}
			l = l->next;
		}
		fn = fn->next_p;
	}
	return (0);
}

void					put_paths_on_map(t_edge **edge, t_list **ways)
{
	t_list				*w;
	t_path 				*r;
	t_edge 				*tmp;

	w = *ways;
	while (w)
	{
		r = w->content;
		while (r->next_p)
		{
			tmp = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
			tmp->cost++;
			if (tmp->cost > 1)
				tmp->cost = 0;
			r = r->next_p;
		}
		w = w->next;
	}
	free_list(ways);
}

void				delete_route(t_path **route, t_edge **edge)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		if (e->v1->mod == 0)
			e->v1->vis = 1;
		r = r->next_p;
	}
}