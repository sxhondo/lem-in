// #include "lem_in.h"
//
// void 				**convert_ver_to_ptrs(t_vertex **ver, int len)
// {
// 	t_vertex 		*v;
// 	void 			**ptr;
// 	int 			i;
//
// 	i = 0;
// 	ptr =  ft_new_ptr_array(len);
// 	v = *ver;
// 	while (v)
// 	{
// 		ptr[i] = v;
// 		i++;
// 		v = v->next;
// 	}
// 	return (ptr);
// }
//
// static t_path 		*select_route(void **ver, int *par, int last)
// {
// 	t_path 			*route = NULL;
// 	t_path			*n;
// 	t_vertex		*v1;
// 	t_vertex 		*v2;
//
//
// 	while (last)
// 	{
// 		v1 = (t_vertex *)ver[last];
// 		// ft_printf("%s\n", v1->name);
// 		n = path_init(v1, NULL);
// 		path_push(&route, n);
// 		last = par[last];
// 	}
// 	// if (path_len(&route) == 1 && route->curr_v->mod == 2)
// 	// {
// 	// 	free(par);
// 	// 	return (NULL);
// 	// }
// 	v1 = (t_vertex *)ver[0];
// 	n = path_init(v1, NULL);
// 	path_push(&route, n);
// 	free(par);
// 	// ft_printf("SELECTING DONE\n");
// 	free(ver);
// 	return (route);
// }
//
// static int			bellman_ford(t_edge **edge, t_vertex **ver,
// 													int *costs, int *par)
// {
// 	int 			st;
// 	int 			fn;
// 	int 			c;
// 	t_edge			*e;
//
// 	e = *edge;
// 	while (e)
// 	{
// 		// ft_printf("%s %s\n", e->v1->name, e->v2->name);
// 		// if (e->v1->mod != 1)
// 		// 	return (0);
// 		st = get_i_by_name(ver, e->v1->name);
// 		fn = get_i_by_name(ver, e->v2->name);
// 		// ft_printf("%d %d\n", st, fn);
// 		c = e->cost;
// 		if (costs[st] + c < costs[fn])
// 		{
// 			// ft_printf("[%s %s]\n", e->v1->name, e->v2->name);
// 			costs[fn] = costs[st] + c;
// 			par[fn] = st;
// 		}
// 		e = e->next;
// 	}
// 	return (1);
// }
//
// static t_path		*get_cheapest_path(t_edge **edge, t_vertex **ver, int len)
// {
// 	int 			v, tmp;
// 	int 			*costs;
// 	int 			*check;
// 	int 			*par;
// 	int 			i, a;
// 	void 			**vp;
//
// 	tmp = len;
// 	costs = ft_new_array(len, INT32_MAX);
// 	costs[0] = 0;
// 	par = ft_new_array(len, 0);
// 	// edge_print(edge);
// 	// vertex_print(ver);
// 	while (tmp--)
// 	{
// 		check = ft_arrdup(costs, v);
// 		i = -1;
// 		while (++i < v)
// 			check[i] = costs[i];
// 		bellman_ford(edge, ver, costs, par);
// 		i = -1;
// 		while (++i <= v)
// 		{
// 			if (check[i] != costs[i])
// 				break ;
// 		}
// 		if (i == v)
// 		{
// 			ft_printf("relaxation stops at %d/%d\n", tmp, len);
// 			break ;
// 		}
// 	}
// 	// ft_printf("BF DONE\n");
// 	// for (int i = 0; i < v; i++)
// 	// 	ft_printf("%d ", par[i]);
// 	free(costs);
// 	vp = convert_ver_to_ptrs(ver, len);
// 	return (select_route(vp, par, len - 1));
// }
//
// static int 				common_ver(t_list **ways, t_path **route)
// {
// 	t_list 				*l;
// 	t_path 				*p;
// 	t_path 				*pp;
//
// 	p = *route;
// 	while (p)
// 	{
// 		l = *ways;
// 		while (l)
// 		{
// 			pp = l->content;
// 			while (pp)
// 			{
// 				if (pp->curr_v->mod == 0 &&
// 					ft_strequ(pp->curr_v->name, p->curr_v->name))
// 					return (1);
// 				pp = pp->next_p;
// 			}
// 			l = l->next;
// 		}
// 		p = p->next_p;
// 	}
// 	return (0);
// }
//
// static t_list 			*get_final_paths(t_edge **edge)
// {
// 	t_list 				*final = NULL;
// 	t_list 				*elem;
// 	t_path 				*route;
//
// 	// edge_print(edge);
// 	while ((route = get_shortest_path(edge)))
// 	{
// 		path_print(&route, 'f');
// 		exit (0);
// 		if (!common_ver(&final, &route))
// 		{
// 			elem = ft_lstnew(route, sizeof(t_path));
// 			ft_lstpushback(&final, elem);
// 		}
// 		exclude_route(&route, edge);
// 		free(route);
// 	}
// 	if (route == NULL)
// 		exit (0);
// 	return (final);
// }
//
// t_list					*solver(t_edge **edge, t_vertex **ver)
// {
// 	t_list 				*final = NULL;
// 	t_list 				*elem;
// 	t_path				*route;
// 	int 				len;
// 	void 				**vp;
//
// 	/* BFS */
// 	// if (!(route = get_shortest_path(edge)))
// 	// 	put_error("cannot reach finish\n", 0);
// 	// exclude_route(&route, edge);
// 	// path_print(&route, 'f');
// 	// path_free(&route);
// 	len = vertex_len(ver);
// 	route = get_cheapest_path(edge, ver, len);
// 	path_print(&route, 'f');
// 	// exclude_route(&route, edge);
// 	exit (0);
// 	// while ((route = get_cheapest_path(edge, ver, len)))
// 	// {
// 	// 	path_print(&route, 'f');
// 	// 	exclude_route_opt(&route, edge);
// 	// 	path_free(&route);
// 	// }
// 	ft_printf("CHEAPEST DONE\n");
// 	return (get_final_paths(edge));
// }
