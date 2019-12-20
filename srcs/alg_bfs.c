#include "lem_in.h"

//static t_vertex			*find_adj(t_edge **edge, t_path **que, char *name)
//{
//	t_edge				*e;
//
//	e = *edge;
//	ft_printf("Iterating over edges\n");
//	while (e)
//	{
//		ft_printf("Checking: %s %s\n", e->v1->name, e->v2->name);
//		if (ft_strequ(name, e->v2->name) && e->cost > 0
//			&& not_in_queue(que, e->v1->name))
//			swap_ver(&e->v2, &e->v1);
//		if (ft_strequ(name, e->v1->name) && e->cost > 0
//			&& not_in_queue(que, e->v2->name))
//			return (e->v2);
//		e = e->next;
//	}
//	ft_printf("Done\n");
//	return (NULL);
//}

static int				not_in_queue(t_list **queue, int curr)
{
	t_list				*q;

	q = *queue;
	while (q)
	{
		if (*((int *)q->content) == curr)
			return (0);
		q = q->next;
	}
	return (1);
}

static size_t			find_adj(t_edge **edge, t_list **queue, int curr)
{
	t_edge				*e;

	e = *edge;
	while (e)
	{
		if (curr == e->v2_i && e->cost > 0)
		{
			swap_ver(&e->v2, &e->v1);
			ft_swap_int(&e->v2_i, &e->v1_i);
		}
		if (curr == e->v1_i && e->cost > 0 && not_in_queue(queue, e->v2_i))
			return (e->v2_i);
		e = e->next;
	}
	return (-1);

}

static int				add_neighbours(t_list **queue, t_edge **edge,
														int curr, int len)
{
	int 				new;
	t_list				*tmp = NULL;


	while ((new = find_adj(edge, queue, curr)) >= 0)
	{
		if (!(tmp = ft_lstnew(&new, sizeof(int))))
			put_error("Cannot allocate memory", 0);
		ft_lstpushback(queue, tmp);
	}
	return (1);
}

static void 			keep_previous_ver(void **ver, t_list *pq, int *trace)
{
	int 				p;
	int 				c;
	t_list 				*ptr;

	p = *(int *)pq->content;
	ptr = pq->next;
	while (ptr)
	{
		c = *(int *)ptr->content;
		if (trace[c] == -1)
			trace[c] = p;
		ptr = ptr->next;
	}
}

t_path					*breadth_first_search(t_edge **edge, void **ver, int len)
{
	t_list				*queue = NULL;
	t_list				*tmp;
	t_list 				*p_q;
	size_t 				i;
	int 				*trace;

	i = 0;
	trace = ft_new_array(len, -1);
	tmp = ft_lstnew(&i, sizeof(int));
	ft_lstpushback(&queue, tmp);
	p_q = queue;
	while ((add_neighbours(&queue, edge, *((int *)p_q->content), len)))
	{
		keep_previous_ver(ver, p_q, trace);
		if (!(p_q = p_q->next))
			break ;
	}
	ft_lstfree(&queue);
	return (trace_route(ver, trace, len - 1));
}