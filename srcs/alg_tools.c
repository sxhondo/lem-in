/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:45:02 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:45:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				swap_ver(t_vertex **v1, t_vertex **v2)
{
	t_vertex		*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

t_path				*trace_route(void **ver, int *trace, int last)
{
	t_path			*route;
	t_path			*n;
	t_vertex		*v1;

	route = NULL;
	if (trace[last] == -1)
	{
		free(trace);
		return (NULL);
	}
	while (last > 0)
	{
		v1 = (t_vertex *)ver[last];
		n = path_init(v1);
		path_push(&route, n);
		last = trace[last];
	}
	v1 = (t_vertex *)ver[0];
	n = path_init(v1);
	path_push(&route, n);
	free(trace);
	return (route);
}

void				exclude_route(t_path **route, t_edge **edge)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		if (e->b == 1 && ft_strequ(r->curr_v->name, e->v1->name))
		{
			swap_ver(&e->v1, &e->v2);
			ft_swap_int(&e->v1_i, &e->v2_i);
		}
		e->b = 0;
		e->cost = -1;
		r = r->next_p;
	}
}