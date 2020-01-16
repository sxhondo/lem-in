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

static size_t		find_adj(t_edge **edge, t_list **queue, int curr)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (curr == e->v1->i && not_in_queue(queue, e->v2->i))
		{
			if (e->del == 0)
				return (e->v2->i);
		}
		e = e->next;
	}
	return (-1);
}

static int			add_neighbours(t_list **queue, t_edge **edge, int curr)
{
	int				new;
	t_list			*tmp;

	while ((new = find_adj(edge, queue, curr)) >= 0)
	{
		if (!(tmp = ft_lstnew(&new, sizeof(int))))
			put_error("Cannot allocate memory", 0);
		ft_lstpushback(queue, tmp);
	}
	return (1);
}

int 				explore_neighbours(t_edge *e, t_list **que,
										int *inq, int *trace, int v)
{
	int 			to;
	t_list			*n;

	while (e)
	{
		if (e->v1->i == v && e->del == 0)
		{
			to = e->v2->i;
			if (inq[to] == 0)
			{
				if (!(n = ft_lstnew(&to, sizeof(int))))
					put_error("cannot allocate memory", 0);
				ft_lstpushback(que, n);
				inq[to] = 1;
				trace[to] = v;
			}
		}
		e = e->next;
	}
}

t_path				*breadth_first_search(t_edge **edge, t_vertex **ver, int s, int f)
{
	t_list			*queue;
	t_list			*n;
	int				*trace;
	int				*inq;
	int 			len;
	int 			v;

	len = vertex_len(ver);
	queue = NULL;

	inq = ft_new_array(len, 0);
	trace = ft_new_array(len, -1);
	if (!(n = ft_lstnew(&s, sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstpushback(&queue, n);
	while (queue)
	{
		v = pop_lst(&queue);
		explore_neighbours(*edge, &queue, inq, trace, v);
	}
	free(inq);
	ft_lstfree(&queue);
	return (trace_route(ver, trace, f));
}