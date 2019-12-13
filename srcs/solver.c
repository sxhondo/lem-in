#include "lem_in.h"

t_path					*exclude_shortest(t_path **path, int **mx)
{
	t_path				*ptr;

	ptr = *path;
	while (ptr)
	{
		if (!ptr->next)
			mx[ptr->node][ptr->parent] = -1;
		mx[ptr->parent][ptr->node] = 0;
		mx[ptr->node][ptr->parent] = -1;
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
			node = path_create_node(i, parent);
			path_push_back(s, node);
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
				node = path_create_node(ptr->node, ptr->parent);
				path_push_front(&path, node);
				finish = ptr->parent;
				break;
			}
			ptr = ptr->next;
		}
	}
	ptr = path_create_node(0, 0);
	path_push_front(&path, ptr);
	path_free(s);
	return (path);
}

t_path 					*get_shortest_path(int **mx, int m_size)
{
	t_path 				*s;
	t_path 				*ptr;
	int 				i;
	int 				tmp;

	s = NULL;
	ptr = path_create_node(0, 0);
	path_push_back(&s, ptr);
	i = 0;
	ptr = s;
	while (ptr && ptr->node != m_size - 1)
	{
		tmp = get_neighbours(&s, mx[i], i, m_size);
//		 int sk2 = path_len(&s) - tmp;
//		 for (t_path *p = s; p; p = p->next)
//		 {
//		 	sk2-- > 0 ?
//		 	ft_printf("{blue}[%d]-->{eoc}{red}%d {eoc}", p->parent, p->node)
//		 	: ft_printf("{blue}[%d]-->{eoc}{yellow}%d {eoc}", p->parent, p->node);
//		 }
//		 ft_printf("\n");
		if ((ptr = ptr->next))
			i = ptr->node;
		else
		{
			path_free(&s);
			return (NULL);
		}
	}
	return (get_reverse_path(&s, m_size - 1));
}

static t_list		*disjoint_path_finding(t_list **ways, int **mx, int m_size)
{
	t_list			*lst;
	t_path			*ptr;

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
		lst = lst->next;
	}
	exclude_overlap(mx, m_size);
	return (NULL);
}

static int			bellman_ford(int **mx, int m_size, int *costs, int *tab)
{
	int 			i;
	int 			j;
	int				iteration;

	iteration = m_size - 1;
	while (iteration--)
	{
		i = -1;
		while (++i < m_size)
		{
			j = -1;
			while (++j < m_size)
			{
				if (mx[i][j] == 0)
					continue;
				if (costs[i] < INT32_MAX && mx[i][j] + costs[i] < costs[j])
				{
					costs[j] = costs[i] + mx[i][j];
					tab[j] = i;
				}
			}
		}
	}
	return (0);
}

static t_path 		*calculate_min_cost(int **mx, int m_size)
{
	t_path			*path = NULL;
	t_path			*node;
	int 			i;
	int 			*costs;
	int 			*tab;

	costs = ft_new_array(m_size, INT32_MAX);
	costs[0] = 0;
	tab = ft_new_array(m_size, 0);
	bellman_ford(mx, m_size, costs, tab);
	i = m_size - 1;
	while (i)
	{
		node = path_create_node(i, tab[i]);
		path_push_front(&path, node);
		i = node->parent;
	}
	node = path_create_node(0, 0);
	path_push_front(&path, node);
	free(costs);
	free(tab);
	return (path);
}

/*
t_list 				*remove_disjoint_vertex(int **mx, int m_size, t_vertex **ver)
{
	t_list			*lst = NULL;
	t_path			*path;
	int 			shortest;

	path = get_shortest_path(mx, m_size);
	shortest = path_len(&path);
	exclude_shortest(&path, mx);
	add_path_to_lst(&lst, path);
	while (is_paths(mx, m_size))
	{

		path = get_shortest_path(mx, m_size);
		if (line_is_busy(&lst, &path, m_size - 1)
			|| path_len(&path) > shortest)
		{
			path_free(&path);
			break ;
		}
		exclude_shortest(&path, mx);
		add_path_to_lst(&lst, path);
	}
	return (lst);
}
*/

static int 				find_min_path(t_list **lst)
{
	t_list				*i;
	t_list				*j;
	t_path				*path_i;
	t_path				*path_j;
	int 				c;

	c = 0;
	i = *lst;
	while (i)
	{
		path_i = i->content;
		j = *lst;
		while (j)
		{
			path_j = j->content;
			if (path_len(&path_i) > path_len(&path_j))
				break ;
			j = j->next;
		}
		if (j == NULL)
			return (c);
		i = i->next;
		c++;
	}
	return (-1);
}

t_list 					*solver(int **mx, int m_size, t_vertex **ver)
{
	t_list				*lst = NULL;
	t_path				*path;

	if (!(path = get_shortest_path(mx, m_size)))
	{
		put_error("can't reach finish", 0);
		return (NULL);
	}
	exclude_shortest(&path, mx);
	add_path_to_lst(&lst, path);
	while (is_paths(mx, m_size))
	{
		path = calculate_min_cost(mx, m_size);
		exclude_shortest(&path, mx);
		add_path_to_lst(&lst, path);
	}
	disjoint_path_finding(&lst, mx, m_size);
	return (lst);
}
