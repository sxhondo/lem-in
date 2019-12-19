#include "lem_in.h"

void 				**convert_ver_to_ptrs(t_vertex **ver, int len)
{
	t_vertex 		*v;
	void 			**ptr;
	int 			i;

	i = 0;
	ptr =  ft_new_ptr_array(len);
	v = *ver;
	while (v)
	{
		ptr[i] = v;
		i++;
		v = v->next;
	}
	return (ptr);
}

int     		     find_ver(void **v, char *name, int size)
{
    t_vertex        *tmp;
    int             i;

    i = 0;
    while (i < size)
    {
		tmp = (t_vertex *)v[i];
		if (ft_strequ(tmp->name, name))
		{
//			ft_printf("[%s] ", tmp->name);
			return (i);
		}
		i++;
    }
	ft_printf("\n");
    return (-1);
}

static int			bellman_ford(t_edge **edge, void **ver, int *cst, int *par, int len)
{
	int 			st;
	int 			fn;
	int 			c;
	t_edge			*e;
	int 			fl;

	fl = 0;
	e = *edge;
	while (e)
	{
        st = find_ver(ver, e->v1->name, len);
		fn = find_ver(ver, e->v2->name, len);
		c = e->cost;
  		if (cst[st] != INT32_MAX && cst[st] + c < cst[fn])
		{
			cst[fn] = cst[st] + c;
			par[fn] = st;
			fl = 1;
		}
  		ft_swap_int(&st, &fn);
		if (e->bi == 1 && cst[st] != INT32_MAX && cst[st] + c < cst[fn])
		{
			cst[fn] = cst[st] + c;
			par[fn] = st;
			fl = 1;
		}
		e = e->next;
	}
	return (fl);
}

int     		     pt(int *p, int size)
{
	t_vertex        *v;
	int             i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d ", p[i]);
		i++;
	}
	ft_printf("\n");
	return (-1);
}

static int 			check_no_end(t_edge **edge)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (e->v1->mod == 2)
			if (e->cost > 0)
				return (1);
		if (e->v2->mod == 2)
			if (e->cost > 0)
				return (1);
		e = e->next;
	}
	return (0);
}

static t_path		*get_cheapest_path(t_edge **edge, void **ver, int len)
{
	int 			*cst;
	int 			*par;
    int 			iter;

	if (!check_no_end(edge))
		return (NULL);
	iter = len;
	cst = ft_new_array(len, INT32_MAX);
	par = ft_new_array(len, 0);
	cst[0] = 0;
	while (iter--)
	{
//		ft_printf("B.F. Relaxation: %d/%d\n", iter, len);
		if (!(bellman_ford(edge, ver, cst, par, len)))
		{
//			ft_printf("B.F. DONE: relaxation stops at %d/%d\n",
//				iter, len);
			break ;
		}
	}
	free(cst);
	return (trace_route(ver, par, len - 1));
}

static void				excluder(t_edge **edge, void **vp, int len, t_list **paths)
{
	t_path				*route;

    while ((route = get_cheapest_path(edge, vp, len)))
	{
		if (path_len(&route) == 2)
		{
			path_free(&route);
			return ;
		}
		exclude_route(&route, edge);
		add_path_to_lst(paths, route);
	}
}

t_list 					*solver(t_edge **edge, t_vertex **ver)
{
	void                **vp;
	int 				len;
	t_list				*paths;
	t_path				*route;

	paths = NULL;
	len = vertex_len(ver);
	vp = convert_ver_to_ptrs(ver, len);
	if (!(route = bfs(edge, vp, len)))
		put_error("no possible solution\n", 0);
	if (path_len(&route) == 2)
	{
		add_path_to_lst(&paths, route);
		free(vp);
		return (paths);
	}
	exclude_route(&route, edge);
	add_path_to_lst(&paths, route);
	excluder(edge, vp, len, &paths);
//	ways_print(&paths);
	cross_path_remover(&paths, edge);
	return (get_closing_paths(edge, vp, len));
}