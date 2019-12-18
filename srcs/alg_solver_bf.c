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

int     		     find_ver(void **v, char *name, int size)
{
    t_vertex        *tmp;
    int             i;

    i = 0;
    while (i < size)
    {
		tmp = (t_vertex *)v[i];
		if (ft_strequ(tmp->name, name))
			return (i);
		i++;
    }
	ft_printf("\n");
    return (-1);
}


static int 			that_way(t_edge **edge, char *name1, char *name2)
{
	t_edge 			*e;

	// edge_print(edge);
	// ft_printf("%s - %s\n", name1, name2);
	e = *edge;
	while (e)
	{
		if (ft_strequ(e->v1->name, name1) && ft_strequ(e->v2->name, name2))
		{
			return (1);
		}
		e = e->next;
	}
	return (0);
}

static int			bellman_ford(t_edge **edge, void **ver, int **cp, int len)
{
	int 			st;
	int 			fn;
	int 			c;
	t_edge			*e;
	int 			fl;

	fl = 0;
	e = *edge;
	// pt(cp[1], len);
	while (e)
	{
        ft_printf("Start %s Fin: %s\n", e->v1->name, e->v2->name);
        st = find_ver(ver, e->v1->name, len);
        fn = find_ver(ver, e->v2->name, len);
		// edge_print(edge);
		// ft_printf("put %d(%s) in %d(%s)\n", st, e->v1->name, fn, e->v2->name);
		// pt(cp[1], len);
		c = e->cost;
		pt(cp[0], len);
		pt(cp[1], len);
		if (cp[0][st] + c < cp[0][fn])
		{
        	ft_printf("%s(%d) from %s(%d)\n", e->v1->name, st, e->v2->name, fn);
			cp[0][fn] = cp[0][st] + c;
			cp[1][fn] = st;
			fl = 1;
			// sleep(1);
		}
		e = e->next;
	}
	return (fl);
}

static t_path		*get_cheapest_path(t_edge **edge, void **ver, int len)
{
	int 			**cp;
	int 			*opt;
    int 			i, iter;

    cp = ft_allocate_mx(2, len, 0);
    i = 0;
    while (++i < len)
        cp[0][i] = INT32_MAX;
    i = -1;
    while (++i < len)
        cp[1][i] = 0;
    iter = len;
	while (iter--)
	{
		if (!(bellman_ford(edge, ver, cp, len)));
		{
			ft_printf("relaxation stops at %d/%d\n", iter, len);
			ft_printf("B.F. DONE\n");
			break ;
		}
	}
	// for (int i = 0; i < len; i++)
	// 	ft_printf("%d ", cp[1][i]);
    // FREE CP!
	return (select_route(ver, edge, cp[1], len - 1));
}

t_list					*solver(t_edge **edge, t_vertex **ver)
{
    void                **vp;
    t_path				*route;
	t_list 				*paths = NULL;
	t_list 				*n;
	int 				len;

	len = vertex_len(ver);
    vp = convert_ver_to_ptrs(ver, len);

	route = bfs(edge, vp, len);
	exclude_route_1(&route, edge);
	path_print(&route, 'f');
	edge_print(edge);

	route = get_cheapest_path(edge, vp, len);
	exclude_route_2(&route, edge);
	path_print(&route, 'f');
	edge_print(edge);
	route = get_cheapest_path(edge, vp, len);
	exclude_route_2(&route, edge);
	edge_print(edge);
	path_print(&route, 'f');

	// edge_print(e)
	exit (0);
}
