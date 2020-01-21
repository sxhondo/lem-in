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

static int			explore_neighbours(t_edge *e, t_list **que, int *inq,
														int *trace, int v)
{
	int 			to;
	t_list			*n;

	while (e)
	{
//		ft_printf("f: %s to: %s %d %d\n", e->v1->name, e->v2->name, e->v1->i, e->v2->i);
		if (e->v1->i == v && e->on == 1 && e->del == 0)
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

	queue = NULL;
	len = vertex_len(ver);
	inq = ft_new_array(len, 0);
	trace = ft_new_array(len, -1);
	if (!(n = ft_lstnew(&s, sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstpushback(&queue, n);
	while (queue)
	{
		v = pop_lst(&queue);
//		t_vertex *tmp = find_ver_by_index(*ver, v);
//		ft_printf("%s m: %d\n", tmp->name, tmp->mark);
		explore_neighbours(*edge, &queue, inq, trace, v);
	}
	free(inq);
	return (trace_route(ver, trace));
}
