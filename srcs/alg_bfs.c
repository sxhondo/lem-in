#include "lem_in.h"

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
		if (ft_strequ(name, e->v2->name) && e->cost > 0
			&& not_in_queue(que, e->v1->name))
			swap_ver(&e->v2, &e->v1);
		if (ft_strequ(name, e->v1->name) && e->cost > 0
			&& not_in_queue(que, e->v2->name))
			return (e->v2);
		e = e->next;
	}
	return (NULL);
}

static int				breadth_first_search(t_path **queue,
										t_edge **edge, t_vertex *curr_v)
{
	t_vertex			*n;
	t_path				*tmp;

	while ((n = find_adj(edge, queue, curr_v->name)))
	{
		tmp = path_init(n);
		path_push_back(queue, tmp);
	}
	return (1);
}

static void 			select_route(void **ver, t_path *q, int *par, int len)
{
	int 				p;
	int 				c;
	t_path 				*ptr;

	p = find_ver(ver, q->curr_v->name, len);
	ptr = q->next_p;
	while (ptr)
	{
//		ft_printf("%s", ptr->curr_v->name, len);
		c = find_ver(ver, ptr->curr_v->name, len);
		if (par[c] == -1)
			par[c] = p;
		ptr = ptr->next_p;
	}
//	ft_printf("BFS - SELECTING\n");
}

t_path					*bfs(t_edge **edge, void **ver, int len)
{
	int 				*par;
	t_path 				*p_q;
	t_path				*queue;

	par = ft_new_array(len, -1);
	queue = path_init(find_start(edge));
	p_q = queue;
	while ((breadth_first_search(&queue, edge, p_q->curr_v)))
	{
//		path_print(&queue, 'f');
		select_route(ver, p_q, par, len);
		if (!(p_q = p_q->next_p) || p_q->curr_v->mod == 2)
			break ;
	}
	path_free(&queue);
	return (trace_route(ver, par, len - 1));
}
