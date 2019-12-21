#include "lem_in.h"

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
//			ft_printf("[%d %d]\n", e->v1_i, e->v2_i);
			swap_ver(&e->v2, &e->v1);
//			ft_printf("[%d %d]\n", e->v1_i, e->v2_i);
			ft_swap_int(&e->v2_i, &e->v1_i);
//			ft_printf("[%d %d]\n", e->v1_i, e->v2_i);
		}
//		if (curr == e->v1_i)
//			if (e->cost > 0)
//			{
////				ft_printf("[%d %d]\n", e->v1_i, e->v2_i);
//				if (not_in_queue(queue, e->v2_i))
//					return (e->v2_i);
//			}
		if (curr == e->v1_i && e->cost > 0 && not_in_queue(queue, e->v2_i))
			return (e->v2_i);
		e = e->next;
	}
	return (-1);
}

static int				add_neighbours(t_list **queue, t_edge **edge, int curr)
{
	int 				new;
	t_list				*tmp;

	while ((new = find_adj(edge, queue, curr)) >= 0)
	{
		if (!(tmp = ft_lstnew(&new, sizeof(int))))
			put_error("Cannot allocate memory", 0);
		ft_lstpushback(queue, tmp);
	}
	return (1);
}

static void 			keep_previous_ver(t_list *pq, int *trace)
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

void 				print_que(t_list **que)
{
	t_list			*q;

	q = *que;
	while (q)
	{
		ft_printf("%d ", *((int *)q->content));
		q = q->next;
	}
}

t_path				*breadth_first_search(t_edge **edge, void **ver, int len)
{
	t_list			*queue;
	t_list			*tmp;
	t_list			*p_q;
	size_t			i;
	int				*trace;

	i = 0;
	queue = NULL;
	trace = ft_new_array(len, -1);
	tmp = ft_lstnew(&i, sizeof(int));
	ft_lstpushback(&queue, tmp);
	p_q = queue;
//	edge_print(edge);
	while ((add_neighbours(&queue, edge, *((int *)p_q->content))))
	{
//		print_que(&queue);
		keep_previous_ver(p_q, trace);
		if (!(p_q = p_q->next))
			break ;
	}
	ft_lstfree(&queue);
	return (trace_route(ver, trace, len - 1));
}