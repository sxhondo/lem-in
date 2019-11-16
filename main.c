#include "lem_in.h"

int 		check_parent(t_path **s, int value, int size)
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

void		get_neighbours(t_path **s, const int *mx, int parent, int size)
{
	t_path		*node;
	int 		i;

	i = 0;
	while (i <= size)
	{
		if (mx[i] != 0 && !check_parent(s, i, size))
		{
			node = create_node(i, parent);
			push_back(s, node);
		}
		i++;
	}
}

int			check_another_path(t_path **s, int finish)
{
	t_path	*ptr;

	ptr = *s;
	while (ptr)
	{
		if (ptr->node == finish)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_path		*get_reverse_path(t_path **s, int finish)
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
				ptr->node = -1;
				ptr->parent = -1;
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

	push_back(&s, create_node(0, 0));
	ptr = s;
	i = 0;
	while (ptr && ptr->node != size - 1)
	{
		get_neighbours(&s, mx[i], i, size - 1);
		for (t_path *p = s; p; p = p->next)
			ft_printf("{blue}[%d]-->{eoc}{red}%d {eoc}", p->parent, p->node);
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
	/* for few paths */
//	while (check_another_path(&s, size - 1))
//		get_reverse_path(&s, size - 1);
	return (get_reverse_path(&s, size - 1));
}

t_path		*exclude_shortest(t_path **path, int **mx)
{
	t_path	*ptr;

	ptr = *path;
	while (ptr)
	{
		if (!ptr->next)
			mx[ptr->node][ptr->parent] = 0;
		mx[ptr->parent][ptr->node] = 0;
		ptr = ptr->next;
	}
	print_matrix(mx, 8);
	return (get_shortest_path(mx, 8));
}

int 		main()
{
	int 	**mx;
	int 	size;
	t_path	*path1;
	t_path	*path2;

	size = 8;
	mx = make_matrix(size);
	print_matrix(mx, size);

	path1 = get_shortest_path(mx, size);
	path2 = exclude_shortest(&path1, mx);

	ft_printf("\n{red}Path 1:{eoc}\n");
	for (t_path *p = path1; p; p = p->next)
		ft_printf("{Bgreen}%d {eoc}", p->node);
	ft_printf("\n{red}Path 2:{eoc}\n");
	for (t_path *p = path2; p; p = p->next)
		ft_printf("{Bgreen}%d {eoc}", p->node);

	free_path(&path1);
	free_path(&path2);
	free_matrix(mx, size);
	return (0);
}