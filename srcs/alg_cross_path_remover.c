#include "lem_in.h"

static void 			reset_map(t_edge **edge)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		e->cost = 1;
		e->bi = 1;
		e = e->next;
	}
}

static void				delete_edge(t_edge **edge, char *name1, char *name2)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		if (ft_strequ(e->v1->name, name1) && ft_strequ(e->v2->name, name2))
			e->cost = 0;
		if (ft_strequ(e->v2->name, name1) && ft_strequ(e->v1->name, name2))
			e->cost = 0;
		e = e->next;
	}
}

static int 				find_overlap(t_list *l, char *name1, char *name2)
{
	t_path				*r;

//	ft_printf("searchin: %s %s\n", name1, name2);
	while (l)
	{
		r = l->content;
		while (r->next_p)
		{
//			ft_printf("checking %s %s\n", r->curr_v->name, r->next_p->curr_v->name);
			if (ft_strequ(r->curr_v->name, name1)
				&& ft_strequ(r->next_p->curr_v->name, name2))
			{
				return (1);
			}
			if (ft_strequ(r->curr_v->name, name2)
				&& ft_strequ(r->next_p->curr_v->name, name1))
			{
				return (1);
			}
			r = r->next_p;
		}
		l = l->next;
	}
	return (0);
}

void					cross_path_remover(t_list **raw, t_edge **edge)
{
	t_list				*l;
	t_path 				*r;

	l = *raw;
	reset_map(edge);
	while (l)
	{
		r = l->content;
		while (r->next_p)
		{
			if (find_overlap(l->next, r->curr_v->name, r->next_p->curr_v->name))
			{
				delete_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
//				edge_print(edge);
			}
			r = r->next_p;
		}
		l = l->next;
	}
	free_list(raw);
}

t_list 					*get_closing_paths(t_edge **edge, void **ver, int len)
{
	t_list				*fin;
	t_path				*r;

	fin = NULL;
	while ((r = bfs(edge, ver, len)))
	{
		if (path_len(&r) == 2)
		{
			path_free(&r);
			free(ver);
			return (fin);
		}
		exclude_route(&r, edge);
		add_path_to_lst(&fin, r);
	}
	free(ver);
	return (fin);
}