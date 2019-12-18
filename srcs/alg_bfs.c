#include "lem_in.h"

static int		         not_in_queue(t_path **que, char *name)
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
		// ft_printf("CURR: %s\n", name);
		if (ft_strequ(name, e->v2->name)
			&& not_in_queue(que, e->v1->name))
		{
			// ft_printf("V1: %s V2: %s\n", e->v1->name, e->v2->name);
			swap_ver(&e->v2, &e->v1);
			e->sw = 1;
		}
		if (ft_strequ(name, e->v1->name)
			&& not_in_queue(que, e->v2->name))
		{
			return (e->v2);
		}
		e = e->next;
	}
	return (NULL);
}

static int				breadth_first_search(t_path **queue,
										t_edge **edge, t_vertex *curr_v)
{
	int 				*par;
	t_vertex			*n;
	t_path				*tmp;

	while ((n = find_adj(edge, queue, curr_v->name)))
	{
		tmp = path_init(n);
		path_push_back(queue, tmp);
	}
	return (1);
}

t_path 				*select_route(void **ver, t_edge **edge, int *par, int last)
{
	t_path 			*route = NULL;
	t_path			*n;
	t_vertex		*v1;
	t_vertex 		*v2;

	ft_printf("\n");
	while (last > 0)
	{
		v1 = (t_vertex *)ver[last];
		v2 = (t_vertex *)ver[par[last]];
		// ft_printf("%s, last: [%d]\n", v1->name, last);
		// sleep (1);
		n = path_init(v1);
		path_push(&route, n);
		last = par[last];
	}
	v1 = (t_vertex *)ver[0];
	n = path_init(v1);
	path_push(&route, n);
	return (route);
}

static void 			trace_route(void **ver, t_path *q, int *par, int len)
{
	int 				p;
	int 				c;
	t_path 				*ptr;

	p = find_ver(ver, q->curr_v->name, len);
	ptr = q->next_p;
	while (ptr)
	{
		c = find_ver(ver, ptr->curr_v->name, len);
		if (par[c] == -1)
			par[c] = p;
		ptr = ptr->next_p;
	}
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
		// path_print(&queue, 'f');
		trace_route(ver, p_q, par, len);
		if (!(p_q = p_q->next_p))
			break ;
	}
	return (select_route(ver, NULL, par, len - 1));
}
