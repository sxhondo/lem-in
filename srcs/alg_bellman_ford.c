#include "lem_in.h"

static void 		*free_tmp_arrays(int *cst, int *par)
{
	free(cst);
	free(par);
	return (NULL);
}

static int			neg_cycle(t_edge **edge, const int *cst)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (cst[e->v1_i] < INT32_MAX && cst[e->v1_i] + e->cost < cst[e->v2_i])
			return (1);
		e = e->next;
	}
	return (0);
}

static int 			check_no_end(t_edge **edge)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		if (e->v1->mod == 2)
			if (e->cost > 0)
				return (1);
		if (e->v2->mod == 2)
			if (e->cost > 0)
				return (1);
		e = e->next;
	}
	return (0);
}

static int			bellman_ford(t_edge **edge, int *cst, int *par)
{
	int 			st;
	int 			fn;
	int 			c;
	t_edge			*e;
	int 			fl;

	fl = 0;
	e = *edge;
	while (e)
	{
		st = e->v1_i;
		fn = e->v2_i;
		c = e->cost;
		if (cst[st] < INT32_MAX && cst[st] + c < cst[fn])
		{
			cst[fn] = cst[st] + c;
			par[fn] = st;
			fl = 1;
		}
		ft_swap_int(&st, &fn);
		if (e->bi == 1 && cst[st] < INT32_MAX && cst[st] + c < cst[fn])
		{
			cst[fn] = cst[st] + c;
			par[fn] = st;
			fl = 1;
		}
		e = e->next;
	}
	return (fl);
}

t_path				*get_cheapest_path(t_edge **edge, void **ver, int len)
{
	int 			*cst;
	int 			*trace;
    register int 	iter;

	cst = ft_new_array(len, INT32_MAX);
	trace = ft_new_array(len, 0);
	iter = len;
	cst[0] = 0;
	while (iter--)
	{
		if (!check_no_end(edge))
			return (free_tmp_arrays(cst, trace));
//		ft_printf("B.F. Relaxation: %d/%d\n", iter, len);
		if (!(bellman_ford(edge, cst, trace)))
		{
//			ft_printf("B.F. DONE: relaxation stops at %d/%d\n",
//				iter, len);
			break ;
		}
	}
	if (neg_cycle(edge, cst))
		return (free_tmp_arrays(cst, trace));
	free(cst);
	return (trace_route(ver, trace, len - 1));
}