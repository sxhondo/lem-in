#include "lem_in.h"

static void 			swap(t_vertex **v1, t_vertex **v2)
{
	t_vertex 			*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void 			        direct_to_finish(t_path **queue, t_edge **edge)
{
	t_path 				*a;
	t_edge 				*tmp;
	t_vertex 			*t_ver;

	a = (*queue)->next_p;
	while (a)
	{
		tmp = find_edge(edge, a->curr_v->name, a->prev_v->name);
		if (!ft_strequ(a->prev_v->name, tmp->v1->name))
            swap(&tmp->v1, &tmp->v2);
		a = a->next_p;
	}
	ft_printf("\n");
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
		e = find_edge(edge, r->curr_v->name, r->prev_v->name);
		// ft_printf("before: %s %s\n", e->v1->name, e->v2->name);
		if (ft_strequ(r->curr_v->name, e->v2->name))
			swap(&e->v1, &e->v2);
		e->cost += e->cost == 1 ? -1 : d;
		// ft_printf("after: %s %s\n", e->v1->name, e->v2->name);
		r = r->prev_p;
	}
	d--;
}

t_path			       *get_parent(t_path **queue, char *name)
{
	t_path				*q;

	q = *queue;
	while (q)
	{
		if (ft_strequ(q->curr_v->name, name))
			return (q);
		q = q->next_p;
	}
	return (NULL);
}

int				         not_in_queue(t_path **que, char *name)
{
	t_path				*q;

	q = *que;
	while (q)
	{
		if (ft_strequ(q->curr_v->name, name))
			return (0);
		q = q->next_p;
	}
	return (1);
}
