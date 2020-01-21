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

static void 		delete_connections(t_edge **edge)
{
	t_edge			*e;
	t_edge			*next;
	t_edge			*del;

	e = *edge;
	while (e->next)
	{
		if (e->on == 0 || e->del == 1)
		{
			next = e->next;
			*edge = next;
			del = e;
			free(del);
			delete_connections(edge);
		}
		if (e->next->on == 0 || e->next->del == 1)
		{
			del = e->next;
			next = e->next->next;
			e->next = next;
			free(del);
			delete_connections(edge);
		}
		e = e->next;
	}
}

static void 		delete_outdated_v(t_vertex *ver, int i)
{
	t_vertex		*v;
	t_vertex		*next;
	t_vertex		*del;

	v = ver;
	while (v->next)
	{
		if (v->next->mod & DIV)
		{
			del = v->next;
			next = v->next->next;
			v->next = next;
			ft_strdel(&del->name);
			free(del);
		}
		v = v->next;
	}
}

void				re_route_edges(t_edge **edge, t_vertex *ver)
{
	t_edge			*e;
	t_vertex		*tmp;

	e = *edge;
	while (e)
	{
		if (e->v2->mod == 0 && (e->v1->mod & DIV))
			e->v1 = find_marked(ver, e->v1->name, OUT);
		if (e->v1->mod == 0 && (e->v2->mod & DIV))
			e->v2 = find_marked(ver, e->v2->name, IN);
		if (e->v1->mod & DIV && e->v2->mod & DIV)
		{
			if ((tmp = find_marked(ver, e->v1->name, IN)))
				e->v1 = tmp;
			if ((tmp = find_marked(ver, e->v2->name, OUT)))
				e->v2 = tmp;
		}
		e = e->next;
	}
}

void				flip_divide(t_path **route, t_edge **edge, t_vertex **ver)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->del = 1;
		if (e->v1->mod == 0)
		{
			e->v1->mod |= DIV;
			vertex_dupl(ver, e->v1->name, IN);
			vertex_dupl(ver, e->v1->name, OUT);
		}
		r = r->next_p;
	}
//	delete_connections(edge);
}

void 				delete_inverse_edges(t_edge *a, t_edge *b, t_path *r)
{
	t_edge			*tmp;

	while (r->next_p)
	{
		if ((tmp = find_edge(&b, r->curr_v->name, r->next_p->curr_v->name)))
			tmp->del = 0;
		r = r->next_p;
	}
	while (a)
	{
		if (a->del == 1)
		{
			tmp = find_edge(&b, a->v1->name, a->v2->name);
			tmp->del = 1;
		}
		a = a->next;
	}
}