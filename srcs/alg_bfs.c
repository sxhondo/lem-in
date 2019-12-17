#include "lem_in.h"

static t_vertex			*find_adj(t_edge **edge, t_path **que, char *name)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		if (e->cost < 0)
		{
			e = e->next;
			continue ;
		}
		if (ft_strequ(e->v1->name, name) && not_in_queue(que, e->v2->name))
			return (e->v2);
		if (ft_strequ(e->v2->name, name) && not_in_queue(que, e->v1->name))
				return (e->v1);
		e = e->next;
	}
	return (NULL);
}

static t_path			*get_reverse_path(t_path *ptr, t_path **queue,
												t_edge **edge)
{
	t_path				*ret = NULL;
	t_path				*node;
	t_path				*tmp;

	ret = path_init(ptr->curr_v, ptr->prev_v);
	while (ret->curr_v->mod != 1)
	{
		tmp = get_parent(queue, ret->prev_v->name);
		node = path_init(tmp->curr_v, tmp->prev_v);
		path_push(&ret, node);
	}
	direct_to_finish(queue, edge);
	path_free(queue);
	return (ret);
}

t_path					*breadth_first_search(t_path *ptr, t_path **queue,
								t_edge **edge, t_vertex *curr_v)
{
	t_vertex			*n;
	t_path				*tmp;

	if (ptr->curr_v->mod == 2)
		return (get_reverse_path(ptr, queue, edge));
	while ((n = find_adj(edge, queue, curr_v->name)))
	{
		tmp = path_init(n, curr_v);
		path_push_back(queue, tmp);
	}
	if (!(ptr = ptr->next_p))
		return (NULL);
	return (breadth_first_search(ptr, queue, edge, ptr->curr_v));
}

t_path					*get_shortest_path(t_edge **edge)
{
	t_path				*queue;

	queue = path_init(find_start(edge), NULL);
	return (breadth_first_search(queue, &queue, edge, queue->curr_v));
}
