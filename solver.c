#include "lem_in.h"

t_path					*exclude_shortest(t_path **path, t_mx *M)
{
	t_path				*ptr;

	ptr = *path;
	while (ptr)
	{
		if (!ptr->next)
			M->mx[ptr->node][ptr->parent] = -1;
		M->mx[ptr->parent][ptr->node] = 0;
		M->mx[ptr->node][ptr->parent] = -1;
		ptr = ptr->next;
	}
	return (NULL);
}

int 					check_parent(t_path **s, int value, unsigned size)
{
	t_path				*ptr;

	ptr = *s;
	while (ptr)
	{
		if (ptr->node == value && value != size)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static int				get_neighbours(t_path **s, const int *mx, int parent, unsigned size)
{
	t_path				*node;
	int 				i;
	int 				q;

	q = 0;
	i = 0;
	while (i < size)
	{
		if (mx[i] != 0 && !check_parent(s, i, size))
		{
			node = create_node(i, parent);
			push_back(s, node);
			++q;
		}
		i++;
	}
	return (q);
}

static t_path			*get_reverse_path(t_path **s, int finish)
{
	t_path				*node;
	t_path				*ptr;
	t_path 				*path = NULL;

	while (finish)
	{
		ptr = *s;
		while (ptr)
		{
			if (ptr->node == finish)
			{
				node = create_node(ptr->node, ptr->parent);
				push_front(&path, node);
				finish = ptr->parent;
				break;
			}
			ptr = ptr->next;
		}
	}
	push_front(&path, create_node(0, 0));
	free_path(s);
	return (path);

}

t_path 					*get_shortest_path(t_mx *M)
{
	t_path 				*s = NULL;
	t_path 				*ptr;
	int 				i;
	int 				tmp;

	push_back(&s, create_node(0, 0));
	ptr = s;
	i = 0;
	while (ptr && ptr->node != M->size - 1)
	{
		tmp = get_neighbours(&s, M->mx[i], i, M->size);
//		int sk2 = path_len(&s) - tmp;
//		for (t_path *p = s; p; p = p->next)
//		{
//			sk2-- > 0 ?
//			ft_printf("{blue}[%d]-->{eoc}{red}%d {eoc}", p->parent, p->node)
//			: ft_printf("{blue}[%d]-->{eoc}{yellow}%d {eoc}", p->parent, p->node);
//		}
//		ft_printf("\n");
		if ((ptr = ptr->next))
			i = ptr->node;
		else
		{
			free_path(&s);
			return (NULL);
		}
	}
	return (get_reverse_path(&s, M->size - 1));
}
static void			disjoint_path_finding(t_list **ways, t_mx *M)
{
	t_list			*lst;
	t_path			*ptr;

	set_to_zero(M->mx, M->size);
	lst = *ways;
	while (lst)
	{
		ptr = lst->content;
		while (ptr)
		{
			if (ptr->node)
				M->mx[ptr->parent][ptr->node] = 1;
			ptr = ptr->next;
		}

		lst = lst->next;
	}
	exclude_overlap(M->mx, M->size);
}

static int			bellman_ford(t_mx *M, int *costs, int *tab)
{
	int 			i;
	int 			j;
	int				iteration;

	iteration = M->size - 1;
	while (iteration--)
	{
		i = -1;
		while (++i < M->size)
		{
			j = -1;
			while (++j < M->size)
			{
				if (M->mx[i][j] == 0)
					continue;
				if (costs[i] < INT32_MAX && M->mx[i][j] + costs[i] < costs[j])
				{
					costs[j] = costs[i] + M->mx[i][j];
					tab[j] = i;
				}
			}
		}
	}
	return (0);
}

static t_path 		*calculate_min_cost(t_mx *M)
{
	t_path			*path = NULL;
	t_path			*node;
	int 			i;
	int 			*costs;
	int 			*tab;

	costs = init_tab(M->size, INT32_MAX);
	tab = init_tab(M->size, 0);
	bellman_ford(M, costs, tab);
	i = M->size - 1;
	while (i)
	{
		node = create_node(i, tab[i]);
		push_front(&path, node);
		i = node->parent;
	}
	push_front(&path, create_node(0, 0));
	free(costs);
	free(tab);
	return (path);
}

int 					solver(t_mx *M, t_vertix **ver)
{
	t_list				*lst = NULL;
	t_path				*path;

	if (!(path = get_shortest_path(M)))
	{
		ft_printf("{red}Can't reach finish.{eoc}\n");
		return (0);
	}
	exclude_shortest(&path, M);
	add_path_to_lst(&lst, path);
	while (is_paths(M))
	{
		path = calculate_min_cost(M);
		exclude_shortest(&path, M);
		add_path_to_lst(&lst, path);
	}
	print_paths(&lst);
	disjoint_path_finding(&lst, M);
	free_list(&lst);
	return (0);
}
