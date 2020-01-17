#include "lem_in.h"

t_vertex			*find_marked(t_vertex *m, char *name, unsigned div)
{
	while (m)
	{
		if (ft_strequ(m->name, name) && m->mod == div)
			return (m);
		m = m->next;
	}
	return (NULL);
}

void				re_route_edges(t_edge **edge, t_vertex *marked)
{
	t_edge			*e;
	t_vertex		*tmp;

	e = *edge;
	while (e)
	{
		if (e->on == 1)
		{
			if (e->v2->mod == 0 && (e->v1->mod & DIV))
				e->v1 = find_marked(marked, e->v1->name, OUT);
			if (e->v1->mod == 0 && (e->v2->mod & DIV))
				e->v2 = find_marked(marked, e->v2->name, IN);
			if (e->v1->mod && e->v2->mod)
			{
				if ((tmp = find_marked(marked, e->v1->name, IN)))
					e->v1 = tmp;
				if ((tmp = find_marked(marked, e->v2->name, OUT)))
					e->v2 = tmp;
			}
		}
		e = e->next;
	}
}

void				flip_divide(t_path **route, t_edge **edge, t_vertex **ver)
{
	t_path			*r;
	t_edge			*e;
	t_edge			*rv;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->on = 0;
		rv = find_edge(edge, r->next_p->curr_v->name, r->curr_v->name);
		if (rv->on == 0)
		{
			e->del = 1;
			rv->del = 1;
		}
		if (e->v1->mod == 0)
		{
			e->v1->mod |= DIV;
			vertex_dupl(ver, e->v1->name, IN);
			vertex_dupl(ver, e->v1->name, OUT);
		}
		r = r->next_p;
	}
	update_indexes(*ver);
}
