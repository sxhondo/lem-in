#include "lem_in.h"

static t_path 		*select_route(t_vertex **ver, int *par, int last)
{
	t_path 			*route = NULL;
	t_path			*n;
	t_vertex		*v1;
	t_vertex 		*v2;

	//!
	while (last)
	{
		ft_printf("a");
		v1 = find_ver_by_index(ver, last);
		v2 = find_ver_by_index(ver, par[last]);
		// ft_printf("[%s %s]\n", v1->name, v2->name);
		n = path_init(v1, v2);
		path_push(&route, n);
		last = par[last];
		// ft_printf("[%s %s]\n", n->curr_v->name, n->prev_v->name);
	}
	if (path_len(&route) == 1 && route->curr_v->mod == 2)
	{
		free(par);
		return (NULL);
	}
	v1 = find_ver_by_index(ver, 0);
	n = path_init(v1, v1);
	path_push(&route, n);
	// path_print(&route, 'f');
	free(par);
	ft_printf("SELECTING DONE\n");
	return (route);
}

static int			bellman_ford(t_edge **edge, t_vertex **ver,
													int *costs, int *par)
{
	int 			st;
	int 			fn;
	int 			c;
	t_edge			*e;

	e = *edge;
	while (e)
	{
		// ft_printf("%s %s\n", e->v1->name, e->v2->name);
		// if (e->v1->mod != 1)
		// 	return (0);
		st = get_i_by_name(ver, e->v1->name);
		fn = get_i_by_name(ver, e->v2->name);
		// ft_printf("%d %d\n", st, fn);
		c = e->cost;
		if (costs[st] + c < costs[fn])
		{
			costs[fn] = costs[st] + c;
			par[fn] = st;
		}
		e = e->next;
	}
	return (1);
}

static t_path		*get_cheapest_path(t_edge **edge, t_vertex **ver)
{
	int 			v, tmp;
	int 			*costs;
	int 			*costs_check;
	int 			*par;
	int 			i, a;

	tmp = v = vertex_len(ver);
	costs = ft_new_array(v, INT32_MAX);
	costs[0] = 0;
	par = ft_new_array(v, 0);

	// edge_print(edge);
	// vertex_print(ver);
	// ft_printf("\n");
	ft_printf("BF\n");
	while (tmp--)
	{
		i = -1;
		costs_check = ft_new_array(v, 0);
		while (++i < v)
			costs_check[i] = costs[i];
		bellman_ford(edge, ver, costs, par);
		i = -1;
		while (++i <= v)
		{
			if (costs_check[i] != costs[i])
				break ;
		}
		if (i == v)
		{
			ft_printf("relaxiation stops at %d/%d\n", tmp, v);
			break ;
		}
	}
	ft_printf("BF_DONE\n");
	// for (int i = 0; i < v; i++)
	// 	ft_printf("%d ", par[i]);
	free(costs);
	return (select_route(ver, par, v - 1));
}

static int 				common_ver(t_list **ways, t_path **route)
{
	t_list 				*l;
	t_path 				*p;
	t_path 				*pp;

	p = *route;
	while (p)
	{
		l = *ways;
		while (l)
		{
			pp = l->content;
			while (pp)
			{
				if (pp->curr_v->mod == 0 &&
					ft_strequ(pp->curr_v->name, p->curr_v->name))
					return (1);
				pp = pp->next_p;
			}
			l = l->next;
		}
		p = p->next_p;
	}
	return (0);
}

static t_list 			*get_final_paths(t_edge **edge)
{
	t_list 				*final = NULL;
	t_list 				*elem;
	t_path 				*route;

	while ((route = get_shortest_path(edge)))
	{
		if (!common_ver(&final, &route))
		{
			elem = ft_lstnew(route, sizeof(t_path));
			ft_lstpushback(&final, elem);
		}
		exclude_route(&route, edge);
		free(route);
	}
	return (final);
}

t_list					*solver(t_edge **edge, t_vertex **ver)
{
	t_list 				*final = NULL;
	t_list 				*elem;
	t_path				*route;

	/* BFS */
	if (!(route = get_shortest_path(edge)))
		put_error("cannot reach finish\n", 0);
	ft_printf("FIRST DONE\n");
	exclude_route(&route, edge);
	path_free(&route);
	while ((route = get_cheapest_path(edge, ver)))
	{
		exclude_route(&route, edge);
		path_free(&route);
	}
	ft_printf("SECOND DONE\n");
	return (get_final_paths(edge));
}
