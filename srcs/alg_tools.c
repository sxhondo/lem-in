#include "lem_in.h"

void				swap_ver(t_vertex **v1, t_vertex **v2)
{
	t_vertex 		*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

static int 			in_list(t_path **route, t_vertex *curr)
{
	t_path			*r;

	r = *route;
	while (r)
	{
		if ((ft_strequ(r->curr_v->name, curr->name)))
			return (1);
		r = r->next_p;
	}
	return (0);
}

t_path				*trace_route(void **ver, int *trace, int last)
{
	t_path 			*route = NULL;
	t_path			*n;
	t_vertex		*v1;

	if (trace[last] == -1)
	{
		free(trace);
		return (NULL);
	}
	while (last > 0)
	{
		v1 = (t_vertex *)ver[last];
		n = path_init(v1);
		path_push(&route, n);
		last = trace[last];
	}
	v1 = (t_vertex *)ver[0];
	n = path_init(v1);
//	free(trace);
	path_push(&route, n);
	return (route);
}

void			    exclude_route(t_path **route, t_edge **edge)
{
	t_path 			*r;
	t_edge 			*e;

	r = *route;
	while (r->next_p)
		r = r->next_p;
	while (r->prev_p)
	{
		e = find_edge(edge, r->curr_v->name, r->prev_p->curr_v->name);
		if (ft_strequ(r->curr_v->name, e->v2->name))
		{
			swap_ver(&e->v1, &e->v2);
			ft_swap_int(&e->v1_i, &e->v2_i);
		}
		e->b = 0;
		e->cost = 0;
		r = r->prev_p;
	}
}
