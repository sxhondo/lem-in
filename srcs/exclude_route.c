#include "lem_in.h"

static int 			duplicate_nodes(t_vertex **ver, void **vp, int len)
{
	int 			i;
	t_vertex		*tmp;
	void 			**new;

	i = 0;
	while (i < len)
	{
		tmp = vp[i];
		if (tmp->div & DIV)
		{
			vertex_new(ver, tmp->name, OUT);
			vertex_new(ver, tmp->name, IN);
		}
		i++;
	}
	return (vertex_len(ver));
}

void 				**divide_nodes(t_edge **edge, t_vertex **ver, void **vp, int len)
{
	int 			i;
	t_vertex		*old;

	i = 0;
	len = duplicate_nodes(ver, vp, len);
	free(vp);
	vp = convert_ver_to_ptrs(ver, len);
	set_indexes_of_ver(edge, vp, len);
	vertex_print(ver);
	while (i < len)
	{
		old = vp[i];
		if (old->div == DIV)
		{
			;
		}
		i++;
	}
	edge_print(*edge);
	exit (0);
}


void				flip_route(t_path **route, t_edge **edge)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		if (e->b == 1 && ft_strequ(r->curr_v->name, e->v1->name))
		{
			swap_ver(&e->v1, &e->v2);
			ft_swap_int(&e->v1_i, &e->v2_i);
		}
		e->b = 0;
		e->cost = -1;
		if (e->v1->mod == UNMOD)
			e->v1->div = DIV;
		if (e->v2->mod == UNMOD)
			e->v2->div = DIV;
		r = r->next_p;
	}
}
