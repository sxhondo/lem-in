#include "lem_in.h"

int 		path_len(t_path **dst)
{
	t_path	*p;
	int 	i;

	i = 0;
	p = *dst;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

t_path 		*create_node(int v, int par)
{
	t_path	*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
		return (NULL);
	p->node = v;
	p->parent = par;
	return (p);
}

void		push_back(t_path **path, t_path *node)
{
	t_path		*tmp;

	tmp = *path;
	if (!*path)
		*path = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
		node->next = NULL;
	}
}

void		push_front(t_path **dst, t_path *node)
{
	if (node != NULL)
	{
		node->next = *dst;
		*dst = node;
	}
}

void		print_paths(t_path **p1, t_path **p2)
{

	ft_printf("Path 1: \n");
	for (t_path *p = *p1; p; p = p->next)
		ft_printf("{Bgreen}%d {eoc}", p->node);
	ft_printf("\nPath 2: \n");
	for (t_path *p = *p2; p; p = p->next)
		ft_printf("{Bgreen}%d {eoc}", p->node);
}

void		free_path(t_path **s)
{
	t_path	*p;
	t_path	*next;

	p = *s;
	while (p)
	{
		next = p->next;
		free (p);
		p = next;
	}
}

void		free_tab(t_list **tab)
{
	t_list	*lst;
	t_list	*next;
	t_path	*ptr;

	lst = *tab;
	while (lst)
	{
		next = lst->next;
		ptr = lst->content;
		free_path(&ptr);
		free(lst);
		lst = next;
	}
}
