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

	ptr = *path;
	while (ptr)
	{
		if (!ptr->next)
			mx[ptr->node][ptr->parent] = -1;
		mx[ptr->parent][ptr->node] = 0;
		mx[ptr->node][ptr->parent] = -1;
		ptr = ptr->next;
	}
}

int				get_neighbours(t_path **s, int *mx, int parent, int size)
{
	t_path		*node;
	int 		i;
	int 		q;
	int 		mark;

	mark = 0;
	q = 0;
	i = 0;
	while (i <= size)
	{
		if (mx[i] < 0 && i != 0)
		{
			node = create_node(i, parent);
			push_back(s, node);
		}
		if (mx[i] != 0 && !check_parent(s, i, size) && mx[i])
		{
			node = create_node(i, parent);
			push_back(s, node);
			++q;
		}
		i++;
	}
	return (q);
}

t_path		*get_reverse_path(t_path **s, int finish, int **mx)
{
	t_path	*ptr;
	t_path 	*path = NULL;

	while (finish)
	{
		ptr = *s;
		while (ptr)
		{
			if (ptr->node == finish)
			{
				push_front(&path, create_node(ptr->node, ptr->parent));
				ft_printf("{Bgreen}%d->{eoc}", ptr->node);
				finish = ptr->parent;
				// ptr->node = -1;
				// ptr->parent = -1;
				break;
			}
			ptr = ptr->next;
		}
	}
	ft_printf("{Bgreen}%d{eoc}\n", (*s)->node);
	free_path(s);
	return (path);

}

t_path 		*get_shortest_path(int **mx, int size)
{
	t_path  *s = NULL;
	t_path	*ptr;
	int 	i;
	int 	old;
	int 	skip;

	push_back(&s, create_node(0, 0));
	ptr = s;
	i = 0;
	while (ptr && ptr->node != size - 1)
	{
		old = get_neighbours(&s, mx[i], i, size - 1);
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

void		put_paths(t_list **tab, int **mx)
{
	t_list	*p;
	t_path	*ptr;

	p = *tab;
	while (p)
	{
		ptr = p->content;
		while (ptr)
		{
			mx[ptr->parent][ptr->node] = 1;
			ptr = ptr->next;
		}
		p = p->next;
	}
}

int 		main()
{
	int 		**mx;
	int 		size;
	t_list	*path_tab = NULL;
	t_path	*edges;

	t_path	*path;

	size = 8;
	mx = make_matrix(size);
	path = get_shortest_path(mx, size);
	exclude_shortest(&path, mx, size);


//	if (size < 5)
//	{
//		ft_printf("\n{red}Least paths:{eoc}\n");
//		if (find_common_vertix(&path1, &path2, size))
//			ft_printf("-Have common vertix. \n");
//		print_paths(&path1, &path2);
//		return (0);
//	}



//	set_to_zero(mx, size);
//	put_paths(&path_tab, mx);
//
//	find_overlap(mx, size);
//	print_matrix(mx, size);
//	free_tab(&path_tab);
//	free_matrix(mx, size);
	return (0);
}
