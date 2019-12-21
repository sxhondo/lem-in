#include "lem_in.h"

static void 			reset_map(t_edge **edge)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		e->cost = 0;
		e->bi = 1;
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
			tmp->cost = -1;
		else
			tmp->cost = 1;
		r = r->next_p;
	}
}

static t_list			*add_shortest_paths(t_list **ways, t_edge **edge,
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
		exclude_route(&fn, edge);
		add_path_to_lst(ways, fn);
	}
	free(ver);
	return (*ways);
}

t_list					*find_overlapping_routes(t_edge **edge,
											t_list **pi, void **vp, int len)
{
	t_path				*route;

	exclude_route((t_path **)&(*pi)->content, edge);
	while ((route = get_cheapest_path(edge, vp, len)))
	{
		if (path_len(&route) == 2)
		{
			path_free(&route);
			break ;
		}
		exclude_route(&route, edge);
		add_path_to_lst(pi, route);
	}
	return (add_shortest_paths(pi, edge, vp, len));
}