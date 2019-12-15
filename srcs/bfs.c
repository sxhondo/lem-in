#include "lem_in.h"

static t_path			*get_parent(t_path **queue, char *name)
{
	t_path				*q;

	q = *queue;
	while (q)
	{
		if (ft_strequ(q->curr->name, name))
			return (q);
		q = q->next;
	}
	return (NULL);
}

static int				not_in_queue(t_path **que, char *name)
{
	t_path				*q;

	q = *que;
	while (q)
	{
		if (ft_strequ(q->curr->name, name))
			return (0);
		q = q->next;
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

static t_path			*get_reverse_path(t_path *ptr, t_path **queue)
{
	t_path				*ret = NULL;
	t_path				*node;
	t_path				*tmp;

	ret = path_duplicate(ptr);
	while (ret->curr->mod != 1)
	{
		tmp = get_parent(queue, ret->prev->name);
		node = path_duplicate(tmp);
		path_push(&ret, node);
	}
	path_free(queue);
	return (ret);
}

t_path					*breadth_first_search(t_path *ptr, t_path **queue,
								t_edge **edge, t_vertex *curr)
{
	t_vertex			*n;

	if (ptr->curr->mod == 2)
		return (get_reverse_path(ptr, queue));
	while ((n = find_adj(edge, queue, curr->name)))
		path_add(queue, n, curr);
	if (!(ptr = ptr->next))
		return (NULL);
	return (breadth_first_search(ptr, queue, edge, ptr->curr));
}

t_path					*get_shortest_path(t_edge **edge)
{
	t_vertex			*start;
	t_path				*queue;
	t_path				*route;

	start = find_start(edge);
	queue = path_init(&start);
	if (!(route = breadth_first_search(queue, &queue, edge, queue->curr)))
		put_error("cannot reach finish", 0);
	return (route);
}