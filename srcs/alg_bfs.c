/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:42:42 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:42:43 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			not_in_queue(t_list **queue, int curr)
{
	t_list			*q;

	q = *queue;
	while (q)
	{
		if (*((int *)q->content) == curr)
			return (0);
		q = q->next;
	}
	return (1);
}

static size_t		find_adj(t_edge **edge, t_list **queue,
							  int curr, const int *cst)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (curr == e->v1_i && not_in_queue(queue, e->v2_i) && e->cost != 0)
		{
			if (e->v2->vis == 0)
				return (e->v2_i);
		}
		if (curr == e->v2_i && not_in_queue(queue, e->v1_i) && e->cost != 0)
		{
			if (e->v1->vis == 0)
			return (e->v1_i);
		}
		e = e->next;
	}
	return (-1);
}

static int			add_neighbours(t_list **queue, t_edge **edge, int curr,
																	int *cst)
{
	int				new;
	t_list			*tmp;

	while ((new = find_adj(edge, queue, curr, cst)) >= 0)
	{
		if (!(tmp = ft_lstnew(&new, sizeof(int))))
			put_error("Cannot allocate memory", 0);
		ft_lstpushback(queue, tmp);
	}
	return (1);
}

static void			keep_previous_ver(t_list *pq, int *trace)
{
	int				p;
	int				c;
	t_list			*ptr;

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

t_path				*breadth_first_search(t_edge **edge, void **ver, int len)
{
	t_list			*queue;
	t_list			*tmp;
	t_list			*p_q;
	int				*trace;
	int				*cst;

	queue = NULL;
	cst = ft_new_array(len, INT32_MAX);
	cst[0] = 0;
	trace = ft_new_array(len, -1);
	tmp = ft_lstnew(&cst[0], sizeof(int));
	ft_lstpushback(&queue, tmp);
	p_q = queue;
	while ((add_neighbours(&queue, edge, *((int *)p_q->content), cst)))
	{
		keep_previous_ver(p_q, trace);
		if (!(p_q = p_q->next))
			break ;
	}
	free(cst);
	ft_lstfree(&queue);
	return (trace_route(ver, trace, len - 1));
}
