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
			par[fn] = st;
		}
		e = e->next;
	}
}

static t_path		*create_route(int *par, int v, t_vertex **ver)
{
	int 			tmp;
	t_vertex		*v_curr;
	t_vertex		*v_par;
	t_path			*route = NULL;
	t_path 			*node;

	tmp = v - 1;
	while (tmp)
	{
		v_curr = find_ver_by_index(ver, tmp);
		v_par = find_ver_by_index(ver, par[tmp]);
		ft_printf("%s %s\n", v_curr->name, v_par->name);
		node = path_init(v_curr, v_par);
		path_push(&route, node);
		tmp = par[tmp];
	}
	v_curr = find_ver_by_index(ver, tmp);
	node = path_init(v_curr, v_curr);
	path_push(&route, node);
	free(par);
	return (route);
}

static t_path		*calculate_min_cost(t_edge **edge, t_vertex **ver)
{
	int 			v, tmp;
	int 			*costs;
	int 			*par;

	tmp = v = vertex_len(ver);
	costs = ft_new_array(v, INT32_MAX);
	costs[0] = 0;
	par = ft_new_array(v, 0);
	while (tmp--)
		bellman_ford(edge, ver, costs, par);
	edge_print(edge);
	if (par[v - 1] == 0)
		return (NULL);
	for (int i = 0; i < v - 1; i++)
		ft_printf("%d ", par[i]);
	ft_printf("\n");
	free(costs);
	return (create_route(par, v, ver));
}

static int 				is_paths(t_edge **edge, int shortest)
{
	int 				i;
	t_edge				*e;

	i = 0;
	e = *edge;
	while (e)
	{
		if (e->cost == 1)
			i++;
		e = e->next;
	}
	if (i < shortest)
		return (0);
	return (1);
}

t_list					*solver(t_edge **edge, t_vertex **ver)
{
	t_path				*route;

	route = get_shortest_path(edge);
	path_print(&route, 'f');
	turn_route_around(edge, &route);
	decrease_cost(edge, &route);
	while ((route = calculate_min_cost(edge, ver)))
	{
		path_print(&route,'f');
		turn_route_around(edge, &route);
		decrease_cost(edge, &route);
	}
	edge_print(edge);
	return (0);
}
