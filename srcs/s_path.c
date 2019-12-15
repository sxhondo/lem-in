#include "lem_in.h"

int 			is_paths(t_edge **edge)
{
	t_path		*f;

	if ((f = get_shortest_path(edge)))
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
	free(path);
	ft_lstpushback(lst, node);
}

t_path				*get_i_path_node(t_path **path, int value)
{
	t_path			*p;

	p = *path;
	while (p && value--)
		p = p->next;
	return (p);
}

int 				path_len(t_path **dst)
{
	t_path			*p;
	int 			i;

	i = 0;
	p = *dst;
	while (p)
	{
		p = p->next;
		i++;
	}
	return (i);
}

t_path 					*path_init(t_vertex **ver)
{
	t_path				*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	p->curr = *ver;
	p->prev = NULL;
	return (p);
}

void					path_push(t_path **dst, t_path *elem)
{
	if (elem != NULL)
	{
		elem->next = *dst;
		*dst = elem;
	}
}

t_path 					*path_duplicate(t_path *dupl)
{
	t_path				*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	p->curr = dupl->curr;
	p->prev = dupl->prev;
	return (p);
}

void					path_add(t_path **dst, t_vertex *elem, t_vertex *prev)
{
	t_path				*p;
	t_path				*tmp;

	if (!(p = ft_memalloc(sizeof(t_path))))
		return (put_error("cannot allocate memory", 0));
	p->curr = elem;
	p->prev = prev;

	tmp = *dst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = p;
	p->next = NULL;
}