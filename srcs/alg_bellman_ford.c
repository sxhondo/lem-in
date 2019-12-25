#include "lem_in.h"

static void 		free_bf(t_bf *bf)
{
	free(bf->id);
	free(bf->d);
	ft_lstfree(&bf->queue);
	free(bf);
}

static t_bf			*init(int len)
{
	int 			*trace;
	int 			*id;
	int 			*d;
	t_bf			*a;

	if (!(trace = ft_new_array(len, -1)))
		put_error("cannot allocate memory", 0);
	if (!(id = ft_new_array(len, 0)))
		put_error("cannot allocate memory", 0);
	if (!(d = ft_new_array(len, INT32_MAX)))
		put_error("cannot allocate memory", 0);
	else
		d[0] = 0;
	if (!(a = ft_memalloc(sizeof(t_bf))))
		put_error("cannot allocate memory", 0);
	else
	{
		a->trace = trace;
		a->id = id;
		a->d = d;
		a->iter = len;
		a->len = len;
	}
	return (a);
}

static int 			relax_edge(t_bf	*a, t_list **que, int v, int to)
{
	int 			flag;
	t_list 			*node;

	flag = 0;
	if (a->d[to] > a->d[v] + a->cost)
	{
		a->d[to] = a->d[v] + a->cost;
		if (a->id[to] == 0)
		{
			if (!(node = ft_lstnew(&to, sizeof(int))))
				put_error("cannot allocate memory", 0);
			ft_lstpushback(que, node);
		}
		else if (a->id[to] == 1)
		{
			if (!(node = ft_lstnew(&to, sizeof(int))))
				put_error("cannot allocate memory", 0);
			ft_lstadd(que, node);
		}
		a->trace[to] = v;
		a->id[to] = 1;
		flag = 1;
	}
	return (flag);
}

static void			explore_neighbours(t_edge **edge, t_list **queue,
															t_bf *a, int v)
{
	int 			to;
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (e->b == 1 && (e->v1_i == v || e->v2_i == v))
		{
			to = (e->v1_i == v) ? e->v2_i : e->v1_i;
			a->cost = e->cost;
			relax_edge(a, queue, v, to);
		}
		else if (e->b == 0 && e->v1_i == v)
		{
			a->cost = e->cost;
			relax_edge(a, queue, v, e->v2_i);
		}
		print_arr(a->trace, a->len);
		print_arr(a->d, a->len);
		print_arr(a->id, a->len);
		e = e->next;
	}

}

t_path				*get_cheapest_path(t_edge **edge, void **ver, int len)
{
	int 			v;
	t_path 			*fin;
	t_list 			*queue;
	t_list 			*node;
	t_bf			*a;

	v = 0;
	queue = NULL;
	a = init(len);
	if (!(node = ft_lstnew(&v, sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstpushback(&queue, node);
	while (queue && a->iter--)
	{
		v = pop_lst(&queue);
		a->id[v] = 1;
		explore_neighbours(edge, &queue, a, v);
	}
	fin = trace_route(ver, a->trace, len - 1);
	free_bf(a);
	return (fin);
}