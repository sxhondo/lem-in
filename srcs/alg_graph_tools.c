#include "lem_in.h"

void					swap_ver(t_vertex **v1, t_vertex **v2)
{
	t_vertex 			*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

t_path				*trace_route(void **ver, int *par, int last)
{
	t_path 			*route = NULL;
	t_path			*n;
	t_vertex		*v1;

	if (par[last] == -1)
		return (NULL);
	while (last > 0)
	{
		v1 = (t_vertex *)ver[last];
		n = path_init(v1);
		path_push(&route, n);
		last = par[last];
	}
	v1 = (t_vertex *)ver[0];
	n = path_init(v1);
	free(par);
	path_push(&route, n);
	return (route);
}


void				    exclude_route(t_path **route, t_edge **edge)
{
	static int			d = -2;
	t_path 				*r;
	t_edge 				*e;

	r = *route;
	while (r->next_p)
		r = r->next_p;
	// path_print(route, 'f');
	while (r->prev_p)
	{
		e = find_edge(edge, r->curr_v->name, r->prev_p->curr_v->name);
//		ft_printf("before: %s %s\n", e->v1->name, e->v2->name);
		if (ft_strequ(r->curr_v->name, e->v2->name))
		{
//			ft_printf("before: %s %s\n", e->v1->name, e->v2->name);
			swap_ver(&e->v1, &e->v2);
		}
		e->bi = 0;
		e->cost = -1;
		// ft_printf("after: %s %s\n", e->v1->name, e->v2->name);
		r = r->prev_p;
	}
	d--;
}
