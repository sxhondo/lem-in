#include "lem_in.h"

//void					exclude_shortest(t_path **path, int **mx)
//{
//	t_path				*ptr;
//
//	ptr = *path;
//	while (ptr)
//	{
//		if (!ptr->next)
//			mx[ptr->node][ptr->parent] = -1;
//		mx[ptr->parent][ptr->node] = 0;
//		mx[ptr->node][ptr->parent] = -1;
//		ptr = ptr->next;
//	}
//}
//
//int 					check_parent(t_path **s, int value, unsigned size)
//{
//	t_path				*ptr;
//
//	ptr = *s;
//	while (ptr)
//	{
//		if (ptr->node == value && value != size)
//			return (1);
//		ptr = ptr->next;
//	}
//	return (0);
//}
//
//static int				get_neighbours(t_path **s, const int *mx, int parent, unsigned size)
//{
//	t_path				*node;
//	int 				i;
//	int 				q;
//
//	q = 0;
//	i = 0;
//	while (i < size)
//	{
//		if (mx[i] != 0 && !check_parent(s, i, size))
//		{
//			node = path_create_node(i, parent);
//			path_push_back(s, node);
//			++q;
//		}
//		i++;
//	}
//	return (q);
//}
//
//static t_path			*get_reverse_path(t_path **s, int finish)
//{
//	t_path				*node;
//	t_path				*ptr;
//	t_path 				*path = NULL;
//
//	while (finish)
//	{
//		ptr = *s;
//		while (ptr)
//		{
//			if (ptr->node == finish)
//			{
//				node = path_create_node(ptr->node, ptr->parent);
//				path_push_front(&path, node);
//				finish = ptr->parent;
//				break;
//			}
//			ptr = ptr->next;
//		}
//	}
//	ptr = path_create_node(0, 0);
//	path_push_front(&path, ptr);
//	path_free(s);
//	return (path);
//}
//
//t_path 					*get_shortest_path(int **mx, int m_size)
//{
//	t_path 				*s;
//	t_path 				*ptr;
//	int 				i;
//	int 				tmp;
//
//	s = NULL;
//	ptr = path_create_node(0, 0);
//	path_push_back(&s, ptr);
//	i = 0;
//	ptr = s;
//	while (ptr && ptr->node != m_size - 1)
//	{
//		tmp = get_neighbours(&s, mx[i], i, m_size);
////		 int sk2 = path_len(&s) - tmp;
////		 for (t_path *p = s; p; p = p->next)
////		 {
////		 	sk2-- > 0 ?
////		 	ft_printf("{blue}[%d]-->{eoc}{red}%d {eoc}", p->parent, p->node)
////		 	: ft_printf("{blue}[%d]-->{eoc}{yellow}%d {eoc}", p->parent, p->node);
////		 }
////		 ft_printf("\n");
//		if ((ptr = ptr->next))
//			i = ptr->node;
//		else
//		{
//			path_free(&s);
//			return (NULL);
//		}
//	}
//	return (get_reverse_path(&s, m_size - 1));
//}

//static void			disjoint_path_finding(t_list **ways, int **mx, int m_size)
//{
//	t_list			*lst;
//	t_path			*ptr;
//
//	lst = *ways;
//	while (lst)
//	{
//		ptr = lst->content;
//		while (ptr)
//		{
//			if (ptr->node)
//				mx[ptr->parent][ptr->node] = 1;
//			ptr = ptr->next;
//		}
//		lst = lst->next;
//	}
//	exclude_overlap(mx, m_size);
//	free_list(ways);
//}
//
//static int			bellman_ford(int **mx, int m_size, int *costs, int *tab)
//{
//	int 			i;
//	int 			j;
//	int				iteration;
//
//	iteration = m_size - 1;
//	while (iteration--)
//	{
//		i = -1;
//		while (++i < m_size)
//		{
//			j = -1;
//			while (++j < m_size)
//			{
//				if (mx[i][j] == 0)
//					continue;
//				if (costs[i] < INT32_MAX && mx[i][j] + costs[i] < costs[j])
//				{
//					costs[j] = costs[i] + mx[i][j];
//					tab[j] = i;
//				}
//			}
//		}
//	}
//	return (0);
//}
//
//static t_path 		*calculate_min_cost(int **mx, int m_size)
//{
//	t_path			*path = NULL;
//	t_path			*node;
//	int 			i;
//	int 			*costs;
//	int 			*tab;
//
//	costs = ft_new_array(m_size, INT32_MAX);
//	costs[0] = 0;
//	tab = ft_new_array(m_size, 0);
//	bellman_ford(mx, m_size, costs, tab);
//	i = m_size - 1;
//	while (i)
//	{
//		node = path_create_node(i, tab[i]);
//		path_push_front(&path, node);
//		i = node->parent;
//	}
//	node = path_create_node(0, 0);
//	path_push_front(&path, node);
//	free(costs);
//	free(tab);
//	return (path);
//}
//
//static int 				check_match(int node, t_path **pth, int last)
//{
//	t_path				*p;
//
//	p = *pth;
//	while (p)
//	{
//		if (p->node != 0 && p->node != last && node == p->node)
//			return (0);
//		p = p->next;
//	}
//	return (1);
//}
//
//static int				check_incident_vertex(t_path **check, t_list **lst, int last)
//{
//	t_path				*p;
//	t_path				*t;
//	t_list				*l;
//
//	p = *check;
//	while (p)
//	{
//		if (p->node != 0 && p->node != last && *lst)
//		{
//			l = *lst;
//			while (l)
//			{
//				if (!(check_match(p->node, (t_path **)&l->content, last)))
//					return (0);
//				l = l->next;
//			}
//		}
//		p = p->next;
//	}
//	return (1);
//}

//static t_list			*remove_disjoint_vertex(int **mx, int m_size,
//																t_vertex **ver)
//{
//	int 				last;
//	t_list				*lst = NULL;
//	t_path				*path;
//
//	last = vertex_len(ver) - 1;
//	while (is_paths(mx, m_size))
//	{
//		path = get_shortest_path(mx, m_size);
//		exclude_shortest(&path, mx);
//		if (check_incident_vertex(&path, &lst, last))
//			add_path_to_lst(&lst, path);
//		else
//			path_free(&path);
//	}
//	return (lst);
//}

//t_list 					*solver(int **mx, int m_size, t_vertex **ver)
//{
//	t_list				*lst = NULL;
//	t_path				*path;
//
//	if (!(path = get_shortest_path(mx, m_size)))
//	{
//		put_error("can't reach finish", 0);
//		return (NULL);
//	}
//	exclude_shortest(&path, mx);
//	add_path_to_lst(&lst, path);
//	while (is_paths(mx, m_size))
//	{
//		path = calculate_min_cost(mx, m_size);
//		exclude_shortest(&path, mx);
//		add_path_to_lst(&lst, path);
//	}
//	disjoint_path_finding(&lst, mx, m_size);
//	return (remove_disjoint_vertex(mx, m_size, ver));
//}

static void				decrease_cost(t_edge **edge, t_path **route)
{
	t_path				*r;

	r = (*route)->next;
	while (r)
	{
		find_edge(edge, r->curr->name, r->prev->name)->cost = -1;
		r = r->next;
	}
	path_free(route);
}

//static int			bellman_ford(int **mx, int m_size, int *costs, int *tab)
//{
//	int 			i;
//	int 			j;
//	int				iteration;
//
//	iteration = m_size - 1;
//	while (iteration--)
//	{
//		i = -1;
//		while (++i < m_size)
//		{
//			j = -1;
//			while (++j < m_size)
//			{
//				if (mx[i][j] == 0)
//					continue;
//				if (costs[i] < INT32_MAX && mx[i][j] + costs[i] < costs[j])
//				{
//					costs[j] = costs[i] + mx[i][j];
//					tab[j] = i;
//				}
//			}
//		}
//	}
//	return (0);
//}
//
//static t_path 		*calculate_min_cost(int **mx, int m_size)
//{
//	t_path			*path = NULL;
//	t_path			*node;
//	int 			i;
//	int 			*costs;
//	int 			*tab;
//
//	costs = ft_new_array(m_size, INT32_MAX);
//	costs[0] = 0;
//	tab = ft_new_array(m_size, 0);
//	bellman_ford(mx, m_size, costs, tab);
//	i = m_size - 1;
//	while (i)
//	{
//		node = path_create_node(i, tab[i]);
//		path_push_front(&path, node);
//		i = node->parent;
//	}
//	node = path_create_node(0, 0);
//	path_push_front(&path, node);
//	free(costs);
//	free(tab);
//	return (path);
//}

static void			bellman_ford(t_edge **edge, t_vertex **ver, int *costs, int *par)
{
	int 			v1;
	int 			v2;
	int 			c;
	t_edge			*e;

	e = *edge;
	while (e)
	{
//		ft_printf("%d ", v1 = get_i_by_name(ver, e->v1->name));
//		ft_printf("%d ", v2 = get_i_by_name(ver, e->v2->name));
//		ft_printf("%d ", c = e->cost);
		v1 = get_i_by_name(ver, e->v1->name);
		v2 = get_i_by_name(ver, e->v2->name);
		c = e->cost;
		if (costs[v1] + c < costs[v2])
		{
			costs[v2] = costs[v1] + c;
			par[v1] = v2;
//			ft_printf("[%d]\n", par[v1]);
		}
		e = e->next;
	}
}

static t_path 		*calculate_min_cost(t_edge **edge, t_vertex **ver)
{
	int 			v, tmp;
	int 			*costs;
	int 			*par;

	edge_print(edge);
	tmp = v = vertex_len(ver);
	costs = ft_new_array(v, INT32_MAX);
	costs[0] = 0;
	par = ft_new_array(v, 0);
	vertex_print(ver);
	while (tmp--)
		bellman_ford(edge, ver, costs, par);
	for (int i = 0; i < v; i++)
		ft_printf("%d ", costs[i]);
	ft_printf("\n");
	for (int i = 0; i < v; i++)
		ft_printf("%d ", par[i]);
	exit (0);
//	return (path);
}

t_list					*solver(t_edge **edge, t_vertex **ver)
{
	t_path				*route;

	route = get_shortest_path(edge);
	decrease_cost(edge, &route);
	while (is_paths(edge))
	{
		route = calculate_min_cost(edge, ver);
	}
	edge_print(edge);

	for (t_path *a = route; a; a = a->next)
		ft_printf("%s->", a->curr->name);
	return (0);
}