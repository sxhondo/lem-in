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

t_path 		*create_node(int v, int par, int cost)
{
	t_path	*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
		return (NULL);
	p->node = v;
	p->parent = par;
	p->cost = cost;
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

void		print_path(t_path **path)
{
	t_path	*ptr;

	ptr = *path;
	while (ptr)
	{
		ft_printf("{green}%d {eoc}", ptr->node);
		ptr = ptr->next;
	}
	ft_printf("\n");
}

void		print_ways(t_list **ways)
{
	t_list	*p;
	t_path	*ptr;
	int 	i;

	i = 0;
	p = *ways;
	ft_printf("\n");
	while (p)
	{
		ft_printf("Path [%d]: \n", i++);
		ptr = p->content;
		print_path(&ptr);
		p = p->next;
	}
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
