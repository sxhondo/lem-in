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

t_path 				*spf(t_edge **edge, void **vp, int len)
{
	int 			v;
	int 			*d;
	int 			*trace;
	int 			to;
	t_edge			*e;
	t_list 			*que;
	t_list 			*node;

	v = 0;
	que = NULL;
	d = ft_new_array(len, INT32_MAX);
	d[0] = 0;
	trace = ft_new_array(len, -1);
	if (!(node = ft_lstnew(&v, sizeof(int))))
		put_error("cannot allocate memory", 0);
	ft_lstadd(&que, node);
	while (que)
	{
		v = pop_lst(&que);
		e = *edge;
		while (e)
		{
			if (e->b && (e->v1_i == v || e->v2_i == v) && e->del != 1)
			{
				to = (e->v1_i == v) ? e->v2_i : e->v1_i;
				rlx(&que, d, v, to, e->cost, trace);
			}
			else if (e->b == 0 && e->v1_i == v && e->del != 1)
			{
				to = e->v2_i;
				rlx(&que, d, v, to, e->cost, trace);
			}
			e = e->next;
		}
	}
	free(d);
	return (trace_route(vp, trace, len - 1));
}