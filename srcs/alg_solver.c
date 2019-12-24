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
//	ft_printf("\n");
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

static void				divide_ver(t_path **route)
{
	t_path				*p;

	p = *route;
	while (p)
	{
		if (p->curr_v->mod == 0)
		{
			p->curr_v->split = 1;
			p->curr_v->out = 0;
			p->curr_v->in = 0;
		}
		p = p->next_p;
	}
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

	while ((route = breadth_first_search(edge, vp, len)))
	{
		divide_ver(&route);
		exclude_route(&route, edge);
//		path_print(&route, 'f');
		add_path_to_lst(&ways, route);
//		edge_print(edge);
	}
	return (add_shortest_paths(&ways, edge, vp, len));

}
