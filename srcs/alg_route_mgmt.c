#include "lem_in.h"

static void 			reset_map(t_edge **edge)
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

t_list					*add_shortest_paths(t_list **ways, t_edge **edge,
											 	 void **ver, int len)
{
	t_list				*w;
	t_path 				*fn;

	w = *ways;
	reset_map(edge);
	while (w)
	{
		put_path((t_path **)&w->content, edge);
		w = w->next;
	}
	free_list(ways);
	while ((fn = breadth_first_search(edge, ver, len)))
	{
		if (path_len(&fn) == 2)
			break ;
		exclude_route(&fn, edge);
		add_path_to_lst(ways, fn);
	}
	free(ver);
	return (*ways);
}
