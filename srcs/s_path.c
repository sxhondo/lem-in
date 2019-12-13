#include "lem_in.h"

int 				line_is_busy(t_list **lst, t_path **path, int last_node)
{
	int 			val;
	t_list			*l;
	t_path			*p;
	t_path			*ptr;

	p = *path;
	while (p)
	{
		val = p->node;
		l = *lst;
		while (l)
		{
			ptr = l->content;
			while (ptr)
			{
				if (ptr->node == val && ptr->node != 0 && ptr->node != last_node)
					return (1);
				ptr = ptr->next;
			}
			l = l->next;
		}
		p = p->next;
	}
	return (0);
}

int 		is_paths(int **mx, int m_size)
{
	t_path	*f;

	if ((f = get_shortest_path(mx, m_size)))
	{
		path_free(&f);
		return (1);
	}
	return (0);
}

void		path_free(t_path **s)
{
	t_path	*p;
	t_path	*next;

	p = *s;
	while (p)
	{
		next = p->next;
		free(p);
		p = next;
	}
}

void		add_path_to_lst(t_list **lst, t_path *path)
{
	t_list	*node;

	if (!(node = ft_lstnew(path, sizeof(t_path))))
		return ;
	free (path);
	ft_lstpushback(lst, node);
//	ft_lstadd(lst, node);
}

t_path				*get_i_path_node(t_path **path, int value)
{
	t_path			*p;

//	if (value < 0)
//		return (NULL);
	p = *path;
	while (p && value--)
		p = p->next;
	return (p);
}

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

t_path 			*path_create_node(int v, int par)
{
	t_path		*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	p->node = v;
	p->parent = par;
	return (p);
}

void			path_push_back(t_path **path, t_path *node)
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

void			path_push_front(t_path **dst, t_path *node)
{
	if (node != NULL)
	{
		node->next = *dst;
		*dst = node;
	}
}

void			path_print(t_path **path, t_vertex **ver)
{
	int 		i;
	t_path		*ptr;

	i = 1;
	ptr = *path;
	while (ptr)
	{
		if (i == 1)
			ft_printf("{red}%s->{eoc}",
					find_ver_by_index(ver, ptr->node)->name);
		else if (i != path_len(path))
			ft_printf("{green}%s->{eoc}",
					find_ver_by_index(ver, ptr->node)->name);
		else if (i == path_len(path))
			ft_printf("{blue}%s{eoc}",
					find_ver_by_index(ver, ptr->node)->name);
		i++;
		ptr = ptr->next;
	}
	ft_printf("\n");
}

void			list_free(t_list **tab)
{
	t_list		*lst;
	t_list		*next;
	t_path		*ptr;

	lst = *tab;
	while (lst)
	{
		next = lst->next;
		ptr = lst->content;
		path_free(&ptr);
		free(lst);
		lst = next;
	}
	*tab = NULL;
}

void			paths_print(t_list **lst, t_vertex **ver)
{
	t_list		*p;
	t_path		*ptr;
	int 		i;

	i = 0;
	p = *lst;
	while (p)
	{
		ft_printf("Path [%d]: ", i++);
		ptr = p->content;
		path_print(&ptr, ver);
		p = p->next;
	}
	ft_printf("\n");
}