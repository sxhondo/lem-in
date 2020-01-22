#include "lem_in.h"

int 					cross_paths(t_path *fn, t_list **ways)
{
	t_list 				*l;
	t_path 				*tmp;

	while (fn)
	{
		l = *ways;
		while (l)
		{
			tmp = l->content;
			while (tmp)
			{
				if (ft_strequ(fn->curr_v->name, tmp->curr_v->name)
					&& fn->curr_v->mod == 0)
					return (1);
				tmp = tmp->next_p;
			}
			l = l->next;
		}
		fn = fn->next_p;
	}
	return (0);
}

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

void				re_route_edges(t_edge **edge, t_vertex *ver)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (e->del == 0 && e->v2->mod == 0 && (e->v1->mod & DIV))
			e->v1 = find_marked(ver, e->v1->name, OUT);
		if (e->del == 0 && e->v1->mod == 0 && (e->v2->mod & DIV))
			e->v2 = find_marked(ver, e->v2->name, IN);
		if (e->del == 0 && e->v1->mod & DIV && e->v2->mod & DIV)
		{
			e->v1 = find_marked(ver, e->v1->name, IN);
			e->v2 = find_marked(ver, e->v2->name, OUT);
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
	update_indexes(*ver);
}

void 				put_paths_on_map(t_edge **edge, t_list *xset)
{
	t_path			*tmp;
	t_edge			*e;
	t_edge			*rv;

	e = *edge;
	while (e)
	{
		e->on = 0;
		e = e->next;
	}
	while (xset)
	{
		tmp = xset->content;
		while (tmp->next_p)
		{
			e = find_edge(edge, tmp->curr_v->name, tmp->next_p->curr_v->name);
			e->on = 1;
			rv = find_edge(edge, tmp->next_p->curr_v->name, tmp->curr_v->name);
			if (rv->on)
			{
				e->del = 1;
				rv->del = 1;
			}
			tmp = tmp->next_p;
		}
		xset = xset->next;
	}
}