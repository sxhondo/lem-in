/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_turns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:44:00 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/22 21:44:00 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			turn_off_path(t_edge **edge, t_path *r)
{
	t_edge			*e;

	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->on = 0;
		r = r->next_p;
	}
}

void				reset_map(t_edge *e)
{
	while (e)
	{
		e->on = 0;
		e = e->next;
	}
}

static void			put_paths_on_map(t_edge **edge, t_list *xset)
{
	t_path			*tmp;
	t_edge			*e;
	t_edge			*rv;

	reset_map(*edge);
	while (xset)
	{
		tmp = xset->content;
		while (tmp->next_p)
		{
			e = find_edge(edge, tmp->curr_v->name, tmp->next_p->curr_v->name);
			e->on = 1;
			rv = find_edge(edge, tmp->next_p->curr_v->name, tmp->curr_v->name);
			if (rv->on)
			{
				e->del = 1;
				rv->del = 1;
			}
			tmp = tmp->next_p;
		}
		xset = xset->next;
	}
}

t_list				*collect_turns(t_edge *edge, t_vertex *ver, t_list *xset,
									int *sf)
{
	t_path			*route;
	t_list			*bset;

	bset = NULL;
	put_paths_on_map(&edge, xset);
	while ((route = breadth_first_search(&edge, &ver, sf[0], sf[1])))
	{
		turn_off_path(&edge, route);
		add_path_to_lst(&bset, route);
	}
	return (bset);
}
