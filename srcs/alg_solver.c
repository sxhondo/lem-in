#include "lem_in.h"

static int			get_index_of_ver(void **v, char *name, int size)
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
	return (-1);
}


static void			set_indexes_of_ver(t_edge **edge, void **ver, int len)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		e->v1_i = get_index_of_ver(ver, e->v1->name, len);
		e->v1->i = e->v1_i;
		e->v2_i = get_index_of_ver(ver, e->v2->name, len);
		e->v2->i = e->v2_i;
		e = e->next;
	}
}

static void			**convert_ver_to_ptrs(t_vertex **ver, int len)
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

t_list 					*solver(int ants, t_edge **edge, t_vertex **ver)
{
	void                **vp;
	int 				len;
	t_list				*ways;
	t_path				*route;

	ways = NULL;
	len = vertex_len(ver);
	vp = convert_ver_to_ptrs(ver, len);
	set_indexes_of_ver(edge, vp, len);
	while ((route = get_cheapest_path(edge, vp, len)))
	{
		if (path_len(&route) == 2)
		{
			add_path_to_lst(&ways, route);
			free(vp);
			return (ways);
		}
		exclude_route(&route, edge);
		add_path_to_lst(&ways, route);
	}
	return (add_shortest_paths(&ways, edge, vp, len));
}
