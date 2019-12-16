#include "lem_in.h"

static t_path			*get_parent(t_path **queue, char *name)
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

static int				not_in_queue(t_path **que, char *name)
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

static t_vertex			*find_adj(t_edge **edge, t_path **que, char *name)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		if (ft_strequ(e->v1->name, name))
		{
			if (not_in_queue(que, e->v2->name))
				return (e->v2);
		}
		if (ft_strequ(e->v2->name, name))
		{
			if (not_in_queue(que, e->v1->name))
				return (e->v1);
		}
		e = e->next;
	}
	return (NULL);
}

static void 			make_graph_directed(t_path **queue, t_edge **edge)
{
	t_path 				*a;
	t_edge 				*tmp;
	t_vertex 			*t_ver;

	a = (*queue)->next_p;
	while (a)
	{
		tmp = find_edge(edge, a->curr_v->name, a->prev_v->name);
		if (!ft_strequ(a->prev_v->name, tmp->v1->name))
		{
			ft_printf("%s swapped with %s | ", a->prev_v->name, tmp->v1->name);
			t_ver = tmp->v1;
			tmp->v1 = tmp->v2;
			tmp->v2 = t_ver;
		}
		a = a->next_p;
	}
	ft_printf("\n");
}

static t_path			*get_reverse_path(t_path *ptr, t_path **queue,
												t_edge **edge)
{
	t_path				*ret = NULL;
	t_path				*node;
	t_path				*tmp;

	ret = path_duplicate(ptr);
	while (ret->curr_v->mod != 1)
	{
		tmp = get_parent(queue, ret->prev_v->name);
		node = path_duplicate(tmp);
		path_push(&ret, node);
	}
	return (ret);
}

t_path					*breadth_first_search(t_path *ptr, t_path **queue,
								t_edge **edge, t_vertex *curr_v)
{
	t_vertex			*n;

	if (ptr->curr_v->mod == 2)
		return (get_reverse_path(ptr, queue, edge));
	while ((n = find_adj(edge, queue, curr_v->name)))
		path_add(queue, n, curr_v);
	if (!(ptr = ptr->next_p))
		return (NULL);
	return (breadth_first_search(ptr, queue, edge, ptr->curr_v));
}

t_path					*get_shortest_path(t_edge **edge, int check)
{
	t_path				*queue;
	t_path				*route;

	queue = path_new();
	queue->curr_v = find_start(edge);
	queue->prev_v = NULL;
	if (!(route = breadth_first_search(queue, &queue, edge, queue->curr_v)))
		put_error("cannot reach finish", 0);
	if (check == 0)
		make_graph_directed(&queue, edge);
	path_free(&queue);
	return (route);
}
