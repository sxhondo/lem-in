/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:14:52 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/22 21:14:53 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_arrays		*init_arrays(t_arrays *arr)
{
	if (!(arr->inq = ft_new_array(arr->len, 0)))
		put_error("cannot allocate memory", 0);
	if (!(arr->trace = ft_new_array(arr->len, -1)))
		put_error("cannot allocate memory", 0);
	return (arr);
}

static void			explore_neighbours(t_edge *e, t_list **que,
														t_arrays *arr, int v)
{
	int				to;
	t_list			*n;

	while (e)
	{
		if (e->v1->i == v && e->on == 1 && e->del == 0)
		{
			to = e->v2->i;
			if (arr->inq[to] == 0)
			{
				if (!(n = ft_lstnew(&to, sizeof(int))))
					put_error("cannot allocate memory", 0);
				ft_lstpushback(que, n);
				arr->inq[to] = 1;
				arr->trace[to] = v;
			}
		}
		e = e->next;
	}
}

t_path				*breadth_first_search(t_edge **edge, t_vertex **ver,
																int s, int f)
{
	t_arrays		*arr;
	t_list			*queue;
	t_list			*n;
	int				v;
	int				*tmp_trace;

	queue = NULL;
	if (!(arr = ft_memalloc(sizeof(t_arrays))))
		put_error("cannot allocate memory", 0);
	arr->len = vertex_len(ver);
	init_arrays(arr);
	if (!(n = ft_lstnew(&s, sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstpushback(&queue, n);
	while (queue)
	{
		v = pop_lst(&queue);
		explore_neighbours(*edge, &queue, arr, v);
	}
	tmp_trace = arr->trace;
	free(arr->inq);
	free(arr);
	return (trace_route(ver, tmp_trace, s, f));
}
