#include "lem_in.h"

t_vertex			*find_marked(t_vertex *m, char *name, unsigned div)
{
	while (m)
	{
		if (ft_strequ(m->name, name) && m->div == div)
			return (m);
		m = m->next;
	}
	return (NULL);
}

void				flip_route(t_path **route, t_edge **edge)
{
	t_path			*r;
	t_edge			*e;

	r = *route;
	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->v1->div = 1;
		e->del = 1;
		e = find_edge(edge, r->next_p->curr_v->name, r->curr_v->name);
		e->cost = -1;
		e->v1->div = 1;
		r = r->next_p;
	}
}

t_vertex			*update_ver(t_vertex **ver)
{
	t_vertex		*v;

	v = *ver;
	while (v)
	{
		if (v->div & DIV && v->mod == 0)
		{
			vertex_dupl(ver, v->name, IN);
			vertex_dupl(ver, v->name, OUT);
		}
		v = v->next;
	}
	return (*ver);
}

//void 				update_3(t_edge *e, t_vertex *m)
//{
//	t_vertex		*tmp;
//
//	while (e)
//	{
//		if (e->del == 0)
//		{
//			if (e->v1->div & DIV && e->v2->div & DIV)
//			{
//				if ((tmp = find_marked(m, e->v1->name, IN)))
//					e->v1 = tmp;
//				if ((tmp = find_marked(m, e->v2->name, OUT)))
//					e->v2 = tmp;
//			}
//		}
//		e = e->next;
//	}
//}

//void 				update_2(t_edge *e, t_vertex *m)
//{
//	t_vertex		*tmp;
//
//	while (e)
//	{
//		if (e->del == 0)
//		{
//			if (e->v1->mod != 0 && e->v2->div & DIV)
//			{
//				if ((tmp = find_marked(m, e->v2->name, OUT)))
//					e->v2 = tmp;
//			}
//			if (e->v2->mod != 0 && e->v1->div & DIV)
//			{
//				if ((tmp = find_marked(m, e->v1->name, IN)))
//					e->v1 = tmp;
//			}
//		}
//		e = e->next;
//	}
//}

//void				update_1(t_edge **edge, t_vertex *marked)
//{
//	t_edge			*e;
//	t_vertex		*tmp;
//
//	e = *edge;
//	while (e)
//	{
//		if (e->del == 0)
//		{
//			if (e->v1->div == 0 && e->v2->div & DIV)
//			{
//				if ((tmp = find_marked(marked, e->v2->name, IN)))
//					e->v2 = tmp;
//			}
//			if (e->v2->div == 0 && e->v1->div & DIV)
//			{
//				if ((tmp = find_marked(marked, e->v1->name, OUT)))
//					e->v1 = tmp;
//			}
//		}
//		e = e->next;
//	}
//}

void				update_1(t_edge **edge, t_vertex *marked)
{
	t_edge			*e;
	t_vertex		*tmp;

	e = *edge;
	while (e)
	{
		if (e->del == 0)
		{
			if (e->v1->div == 0 && e->v2->div & DIV)
			{
				if ((tmp = find_marked(marked, e->v2->name, IN)))
					e->v2 = tmp;
			}
			if (e->v2->div == 0 && e->v1->div & DIV)
			{
				if ((tmp = find_marked(marked, e->v1->name, OUT)))
					e->v1 = tmp;
			}
			if (e->v1->mod != 0 && e->v2->div & DIV)
			{
				if ((tmp = find_marked(marked, e->v2->name, OUT)))
					e->v2 = tmp;
			}
			if (e->v2->mod != 0 && e->v1->div & DIV)
			{
				if ((tmp = find_marked(marked, e->v1->name, IN)))
					e->v1 = tmp;
			}
			if (e->v1->div & DIV && e->v2->div & DIV)
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

t_list 				*update_graph(t_edge **edge, t_vertex **ver,
							t_path *route, t_list *ex_set)
{
	flip_route(&route, edge);

	update_ver(ver);
	update_1(edge, *ver);
	update_indexes(*ver);

	add_path_to_lst(&ex_set, route);
	return (ex_set);
}