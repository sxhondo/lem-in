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

void 				print_que(t_list **que, void **ver)
{
	t_list			*q;

	q = *que;
	while (q)
	{
		ft_printf("%s ", ((t_vertex **)ver)[*((int *)q->content)]->name);
		q = q->next;
	}
	ft_printf("\n");
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

//static size_t			find_adj(t_edge **edge, t_list **queue, int curr)
//{
//	t_edge				*e;
//
//	e = *edge;
//	while (e)
//	{
////		ft_printf("%s - %s\n", e->v1->name, e->v2->name);
//		if (curr == e->v1_i && not_in_queue(queue, e->v2_i) && e->cost != 0)
//			return (e->v2_i);
//		if (e->b && curr == e->v2_i && not_in_queue(queue, e->v1_i) && e->cost != 0)
//			return (e->v1_i);
//		e = e->next;
//	}
//	return (-1);
//}
//
//static size_t			find_inout(t_edge **edge, t_list **queue, int curr, void **ver)
//{
//	t_edge				*e;
//
//	e = *edge;
//	while (e)
//	{
//		if (curr == e->v1_i)
//		{
//			if (not_in_queue(queue, e->v2_i))
//			{
//				if (((t_vertex **)ver)[curr]->out)
//					return (e->v2_i);
//			}
//		}
//		if (curr == e->v2_i)
//		{
//			if (not_in_queue(queue, e->v1_i) && e->v1->split)
//				return (e->v1_i);
//		}
//		e = e->next;
//	}
//	return (-1);
//}

static int 				find_adj(t_edge **edge, t_list **queue, t_vertex *curr)
{
	t_edge				*e;

	e = *edge;
	if (curr->split)
	{
		if (curr->in)
			while (e)
			{
				if (curr->i == e->v1_i && not_in_queue(queue, e->v2_i)
				&& e->v2->split && e->cost >= 0)
				{
//					ft_printf("(%s)\n", e->v2->name);
					e->v2->out = 1;
					return (e->v2_i);
				}
				if (e->b && curr->i == e->v2_i && not_in_queue(queue, e->v1_i)
			 	&& e->v1->split && e->cost >= 0)
				{
					e->v1->out = 1;
					return (e->v1_i);
				}
				e = e->next;
			}
	}
	e = *edge;
	while (e)
	{
		if (curr->i == e->v1_i && not_in_queue(queue, e->v2_i) && e->cost >= 0)
			return (e->v2_i);
		if (e->b && curr->i == e->v2_i && not_in_queue(queue, e->v1_i) && e->cost >= 0)
			return (e->v1_i);
		e = e->next;
	}
	return (-1);
}

static int				add_neighbours(t_list **queue, t_edge **edge,
														void **ver, int curr, int len)
{
	int 				new;
	t_list				*tmp;
	t_vertex			*cur;

	cur = ver[curr];
//	edge_print(edge);
//	ft_printf("current: [%s]\nnew: ", cur->name);
	while ((new = find_adj(edge, queue, cur)) > 0)
	{
//		ft_printf("%s ", ((t_vertex **)ver)[new]->name);
		if (((t_vertex **)ver)[new]->split && ((t_vertex **)ver)[new]->out == 0)
			((t_vertex **)ver)[new]->in = 1;
		if (!(tmp = ft_lstnew(&new, sizeof(int))))
			put_error("cannot allocate memory", 0);

		ft_lstpushback(queue, tmp);
//		print_que(queue, ver);
	}
//	print_void_ver(ver, len);
//	ft_printf("\n");
	return (1);
}

t_path				*breadth_first_search(t_edge **edge, void **ver, int len)
{
	t_list			*queue = NULL;
	t_list			*tmp;
	t_list			*p_q;
	size_t			i = 0;
	int				*trace;


	trace = ft_new_array(len, -1);
	tmp = ft_lstnew(&i, sizeof(int));
	ft_lstpushback(&queue, tmp);

//	edge_print(edge);
	p_q = queue;
	while ((add_neighbours(&queue, edge, ver, *((int *)p_q->content), len)))
	{
//		print_que(&queue, ver);
		keep_previous_ver(p_q, trace);
		if (!(p_q = p_q->next))
			break ;
	}
	ft_lstfree(&queue);

	t_path *a;
	a = trace_route(ver, trace, len - 1);
//	path_print(&a, 'f');
//	print_void_ver(ver, len);
	return (a);
}