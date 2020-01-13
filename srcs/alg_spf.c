#include "lem_in.h"

static int 			rlx(t_list **que, int *d, int v, int to, int ecost,
																	int *trace)
{
	t_list 			*node;

	if (d[to] > d[v] + ecost)
	{
		d[to] = d[v] + ecost;
		if (d[to] != INT32_MAX)
		{
			node = ft_lstnew(&to, sizeof(int));
			ft_lstpushback(que, node);
		}
		trace[to] = v;
	}
}

//t_path 				*spf(t_edge **edge, void **vp, int len)
//{
//	int 			v;
//	int 			*d;
//	int 			*trace;
//	int 			to;
//	t_edge			*e;
//	t_list 			*que;
//	t_list 			*node;
//
//	v = 0;
//	que = NULL;
//	d = ft_new_array(len, INT32_MAX);
//	d[0] = 0;
//	trace = ft_new_array(len, -1);
//	if (!(node = ft_lstnew(&v, sizeof(int))))
//		put_error("cannot allocate memory", 0);
//	ft_lstadd(&que, node);
//	while (que)
//	{
//		v = pop_lst(&que);
//		e = *edge;
//		while (e)
//		{
//			if (e->b && (e->v1_i == v || e->v2_i == v) && e->del != 1)
//			{
//				to = (e->v1_i == v) ? e->v2_i : e->v1_i;
//				rlx(&que, d, v, to, e->cost, trace);
//			}
//			else if (e->b == 0 && e->v1_i == v && e->del != 1)
//			{
//				to = e->v2_i;
//				rlx(&que, d, v, to, e->cost, trace);
//			}
//			e = e->next;
//		}
//	}
//	free(d);
//	return (trace_route(vp, trace, len - 1));
//}

static int 				relax_edge(t_list **que,
		int *inq, int *cnt, int *d, int *trace, int v, int to, int cost, int len)
{
	t_list 				*node;

	if (d[v] + cost < d[to])
	{
		d[to] = d[v] + cost;
		if (inq[to] == 0)
		{
			if (!(node = ft_lstnew(&to, sizeof(int))))
				put_error("cannot allocate memory", 0);
			ft_lstpushback(que, node);
			inq[to] = 1;
			cnt[to]++;
			if (cnt[to] > len)
				return (0);
		}
		trace[to] = v;
	}
	return (1);
}

int 					explore_neighbours(t_edge *e, t_list **que,
		int v, int *d, int *trace, int *cnt, int *inq, int len)
{
	int 				to;
	int 				cost;

	while (e)
	{
		if (e->b == 1 && (e->v1_i == v || e->v2_i == v))
		{
			to = (e->v1_i == v) ? e->v2_i : e->v1_i;
			cost = e->cost;
			if (!(relax_edge(que, inq, cnt, d, trace, v, to, cost, len)))
				return (0);
		}
		else if (e->b == 0 && e->v1_i == v)
		{
			to = e->v2_i;
			cost = e->cost;
			if (!(relax_edge(que, inq, cnt, d, trace, v, to, cost, len)))
				return (0);
		}
		e = e->next;
	}
	return (1);
}

t_path 					*spf_algorithm(t_edge **edge, void **vp, int len)
{
	int 				*cnt;
	int 				*inq;
	int 				*trace;
	int 				*d;
	int 				v;
	t_list 				*que;
	t_list 				*node;

	que = NULL;
	d = ft_new_array(len, INT32_MAX);
	d[0] = 0;
	trace = ft_new_array(len, -1);
	cnt = ft_new_array(len, 0);
	inq = ft_new_array(len, 0);
	if (!(node = ft_lstnew(&d[0], sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstpushback(&que, node);
	while (que)
	{
		v = pop_lst(&que);
		inq[v] = 0;
		if (!(explore_neighbours(*edge, &que, v, d, trace, cnt, inq, len)))
		{
			ft_printf("neg cycle\n");
			break ;
		}
	}
	free(cnt);
	free(inq);
	free(d);
	return (trace_route(vp, trace, len - 1));
}
