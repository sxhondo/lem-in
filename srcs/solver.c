#include "lem_in.h"

static void				turn_route_around(t_edge **edge, t_path **route)
{
	t_vertex 			*ver;
	t_path				*tmp;
	t_edge 				*e_tmp;


	tmp = *route;
	while (tmp->next_p)
		tmp = tmp->next_p;
	while (tmp->prev_p)
	{
		e_tmp = find_edge(edge, tmp->prev_v->name, tmp->curr_v->name);
		ft_printf("%s swapped with %s | ", e_tmp->v1->name, e_tmp->v2->name);
		ver = e_tmp->v1;
		e_tmp->v1 = e_tmp->v2;
		e_tmp->v2 = ver;
		tmp = tmp->prev_p;
	}
	ft_printf("\n");
}

static void				decrease_cost(t_edge **edge, t_path **route)
{
	t_path				*r;

	r = (*route)->next_p;
	while (r)
	{
		find_edge(edge, r->curr_v->name, r->prev_v->name)->cost = -1;
		r = r->next_p;
	}
	path_print(route, 'f');
	path_free(route);
}

static void			bellman_ford(t_edge **edge, t_vertex **ver, int *costs, int *par)
{
	int 			st;
	int 			fn;
	int 			c;
	t_edge			*e;

	e = *edge;
	while (e)
	{
		st = get_i_by_name(ver, e->v1->name);
		fn = get_i_by_name(ver, e->v2->name);
		c = e->cost;
		if (costs[st] + c < costs[fn])
		{
			costs[fn] = costs[st] + c;
			par[st] = fn;
		}
		e = e->next;
	}
}

static t_path 		*calculate_min_cost(t_edge **edge, t_vertex **ver)
{
	int 			v, tmp;
	int 			*costs;
	int 			*par;
	t_path 			*route = NULL;

	tmp = v = vertex_len(ver);
	costs = ft_new_array(v, INT32_MAX);
	costs[0] = 0;
	par = ft_new_array(v, 0);
	vertex_print(ver);
	while (tmp--)
		bellman_ford(edge, ver, costs, par);

	for (int i = 0; i < v; i++)
		ft_printf("%d", par[i]);
//	return (path);
}

t_list					*solver(t_edge **edge, t_vertex **ver)
{
	t_path				*route;

	route = get_shortest_path(edge, 0);
	turn_route_around(edge, &route);
	decrease_cost(edge, &route);
	while (is_paths(edge))
	{
		route = calculate_min_cost(edge, ver);
	}
	return (0);
}
