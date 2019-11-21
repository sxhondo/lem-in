#include "lem_in.h"

int 			check_parent(t_path **s, int value, int size)
{
	t_path	*ptr;

	ptr = *s;
	while (ptr)
	{
		if (ptr->node == value && value != size)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_path		*exclude_shortest(t_path **path, int **mx, int size)
{
	t_path	*ptr;
	t_path	*save;

	print_matrix(mx, size);
	ptr = *path;
	while (ptr)
	{
		if (!ptr->node && !ptr->parent)
		{
			save = ptr;
			ptr = ptr->next;
			free (save);
		}
		if (!ptr->next)
			mx[ptr->node][ptr->parent] = -1;
		ft_printf("{blue}[%d]-->{red}[%d]{eoc}", ptr->parent, ptr->node);
		mx[ptr->parent][ptr->node] = 0;
		mx[ptr->node][ptr->parent] = -1;
		ptr = ptr->next;
	}
	return (NULL);
}

int				get_neighbours(t_path **s, int *mx, int parent, int size, int cost)
{
	t_path		*node;
	int 		i;
	int 		q;

	q = 0;
	i = 0;
	while (i <= size)
	{
		if (mx[i] != 0 && !check_parent(s, i, size))
		{
			node = create_node(i, parent, cost);
			push_back(s, node);
			++q;
		}
		i++;
	}
	return (q);
}

t_path		*get_reverse_path(t_path **s, int finish, int **mx)
{
	t_path	*node;
	t_path	*ptr;
	t_path 	*path = NULL;

	while (finish)
	{
		ptr = *s;
		while (ptr)
		{
			if (ptr->node == finish)
			{
				node = create_node(ptr->node, ptr->parent, ptr->cost);
				push_front(&path, node);
//				ft_printf("{Bgreen}%d->{eoc}", ptr->node);
				finish = ptr->parent;
				break;
			}
			ptr = ptr->next;
		}
	}
//	node = create_node(0, 0);
//	push_front(&path, node);
//	ft_printf("{Bgreen}%d{eoc}\n", (*s)->node);
	free_path(s);
	return (path);

}

int			*init_tab(int **mx, int size)
{
	int 	max;
	int 	*tab;

	max = count_max_edges(mx, size);
	tab = (int *)malloc(sizeof(int *) * size);
	for (int i = 0; i < size; i++)
		tab[i] = max;
	tab[0] = 0;
	return (tab);

}

void		print_tab(int *tab, int size)
{
	int 	i;
	int 	ch = 'A';

	ft_printf("\n");
	for (i = 0; i < size; i++)
		ft_printf("{red}%3c{eoc}", ch++);
	ft_printf("\n");
	for (i = 0; i < size; i++)
		ft_printf("{cyan}%3d{eoc}", tab[i]);
	ft_printf("\n\n");
}

void		relax_cost(int *mx, int pos, int *tab, int size)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		if (mx[i] != 0)
		{
			if (mx[i] + tab[pos] < tab[i])
				tab[i] = mx[i] + tab[pos];
		}
		i++;
	}
}

int			*calculate_min_cost(int **mx, int size)
{
	int 	i;
	int 	iter;
	int 	*tab;

	tab = init_tab(mx, size);
	iter = size - 1;
	while (iter--)
	{
		i = -1;
		while (++i < size)
			relax_cost(mx[i], i, tab, size);
	}
	return (tab);
}

t_path 		*get_shortest_edges(int **mx, int size)
{
	t_path  *s = NULL;
	t_path	*ptr;
	int 	i;
	int 	old;
	int 	skip;
	int 	*tab;

	tab = calculate_min_cost(mx, size);
	push_back(&s, create_node(0, 0, 0));
	ptr = s;
	i = 0;
	while (ptr && ptr->node != size - 1)
	{
		old = get_neighbours(&s, mx[i], i, size - 1, tab[i]);
		skip = path_len(&s) - old;
		for (t_path *p = s; p; p = p->next)
		{
			skip-- > 0 ? ft_printf("{blue}[%d]-->{eoc}{red}%d {eoc}", p->parent, p->node)
				: ft_printf("{blue}[%d]-->{eoc}{yellow}%d {eoc}", p->parent, p->node);
		}
		ft_printf("\n%d - discovered\n--------\n", ptr->node);
		if ((ptr = ptr->next))
			i = ptr->node;
		else
		{
			ft_printf("{Bred}Can't reach finish.{eoc}\n");
			free_path(&s);
			return (NULL);
		}
	}
	return (get_reverse_path(&s, size - 1, mx));
}



// t_path		*choose_cheapest(t_path **s, t_path **N, int *prices)
// {
// 	t_path	*p;
// 	int 	i;
// 	int 	len;
// 	int 	*arr;
// 	int 	tmp;
//
// 	len = path_len(N);
// 	if (len > 0)
// 		arr = (int *)malloc(sizeof(int *) * len);
// 	else
// 		return (NULL);
// 	p = *N;
// 	i = 0;
// 	while (p)
// 	{
// 		arr[i] = p->node;
// 		i++;
// 		p = p->next;
// 	}
//
// 	for (int q = 0; q < len; q++)
// 		ft_printf("%3d", arr[q]);
// 	if (len == 2)
// 	{
// 		if (arr[0] > arr[1])
// 		{
// 			tmp = arr[0];
// 			arr[0] = arr[1];
// 			arr[1] = tmp;
// 		}
// 	}
//
// 	i = -1;
// 	while (++i < len)
// 		push_back(s, create_node(arr[i], 0));


//	t_path	*i;
//	t_path	*j;
//	t_path	*res;
//
//	i = *N;
//	while (i)
//	{
//		j = *N;
//		while (j)
//		{
//			if (prices[j->node] < prices[i->node])
//				break;
//			j = j->next;
//		}
//		if (!j)
//		{
//			ft_printf("{green}[CHEAPEST: %d]\n{eoc}", i->node);
//			res = create_node(i->node, i->parent);
//			push_back(s, res);
//			return (i);
//		}
//		i = i->next;
//	}
//	return (NULL);
// }

// int 			is_member_of_set(t_path **s, int value, int size)
// {
// 	t_path	*ptr;
//
// 	ptr = *s;
// 	while (ptr)
// 	{
// 		if (ptr->node == value && value != size)
// 			return (1);
// 		ptr = ptr->next;
// 	}
// 	return (0);
// }

// t_path		*get_neighbours_by_cost(t_path **s, int *mx, int par, int size)
// {
// 	int 	i;
// 	t_path	*N = NULL;
//
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (mx[i] != 0 && !is_member_of_set(s, i, size))
// 			push_front(&N, create_node(i, par));
// 		i++;
// 	}
// 	for (t_path *p = N; p; p = p->next)
// 		ft_printf("\n{red}[PRETENDERS: %d]{eoc} ", p->node);
// 	ft_printf("\n");
// 	return (N);
// }

// t_path		*get_shortest_weight(int **mx, int size)
// {
// 	int 	i;
// 	int 	*tab;
// 	int 	skip;
// 	t_path	*s = NULL;
// 	t_path	*ptr;
// 	t_path	*neighs;
//
// 	print_matrix(mx, size);
//
// 	tab = calculate_min_cost(mx, size);
// 	i = 0;
// 	push_back(&s, create_node(0, 0));
// 	ptr = s;
// 	while (ptr && ptr->node != size - 1)
// 	{
// 		if ((neighs = get_neighbours_by_cost(&s, mx[i], i, size)))
// 		{
// 			choose_cheapest(&s, &neighs, tab);
// 			skip = path_len(&s) - path_len(&neighs);
// 		}
// 		print_tab(tab, size);
// 		for (t_path *p = s; p; p = p->next)
// 		{
// 			skip-- >= 0 ? ft_printf("{blue}[%d]->{red}%d{eoc} ", p->parent, p->node) :
// 			ft_printf("{blue}[%d]->{yellow}%d{eoc} ", p->parent, p->node);
// 		}
// 		ft_printf("\n");
// 		if ((ptr = ptr->next))
// 			i = ptr->node;
// 		else
// 		{
// 			ft_printf("{Bred}Can't reach finish.{eoc}\n");
// 			free_path(&s);
// 			free (tab);
// 			return (NULL);
// 		}
// 	}
// 	free (tab);
// 	return (s);
// }
//
void		disjoint_path_finding(t_list **ways, int **mx, int size)
{
	t_list	*lst;
	t_path	*ptr;

	print_ways(ways);
	set_to_zero(mx, size);
	lst = *ways;
	while (lst)
	{
		ptr = lst->content;
		while (ptr)
		{
			if (ptr->node)
				mx[ptr->parent][ptr->node] = 1;
			ptr = ptr->next;
		}
		print_matrix(mx, size);
		lst = lst->next;
	}
	exclude_overlap(mx, size);
}

int 		main()
{
	int 		**mx;
	int 		size;
	t_list		*ways = NULL;
	t_path		*path;


	size = 8;
	mx = make_matrix(size);

	while ((path = get_shortest_edges(mx, size)))
		{
			print_path(&path);
			exclude_shortest(&path, mx, size);
			ft_lstadd(&ways, ft_lstnew(path, sizeof(t_path)));
		}
		print_ways(&ways);
	// disjoint_path_finding(&ways, mx, size);
	// while ((path = get_shortest_weight(mx, size)))
	// {
	// 	print_matrix(mx, size);
	// 	print_ways(&ways);
	// 	exclude_shortest(&path, mx, size);
	// 	print_matrix(mx, size);
	// 	ft_lstadd(&ways, ft_lstnew(path, sizeof(t_path)));
	// }
	// disjoint_path_finding(&ways, mx, size);
	// print_matrix(mx, size);
	// free_tab(&ways);
	// free_matrix(mx, size);
	return (0);
}
