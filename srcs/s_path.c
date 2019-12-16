#include "lem_in.h"

int 			is_paths(t_edge **edge)
{
	t_path		*f;

	if ((f = get_shortest_path(edge, 1)))
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
		next = p->next_p;
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
		p = p->next_p;
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
		p = p->next_p;
		i++;
	}
	return (i);
}

t_path 					*path_new()
{
	t_path 				*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	return (p);
}

void 					path_pback(t_path **dst, t_path *elem)
{
	t_path 				*tmp;

	tmp = *dst;
	while (tmp->next_p)
		tmp = tmp->next_p;
	tmp->next_p = elem;
	elem->prev_p = elem;
	elem->next_p = NULL;
}

void					path_push(t_path **dst, t_path *elem)
{
	if (elem != NULL)
	{
		elem->next_p = *dst;
		elem->next_p->prev_p = elem;
		elem->prev_p = NULL;
		*dst = elem;
	}
}

t_path 					*path_duplicate(t_path *dupl)
{
	t_path				*p;

	p = path_new();
	p->curr_v = dupl->curr_v;
	p->prev_v = dupl->prev_v;
	return (p);
}

void					path_push_init(t_path **dst, t_vertex *v1, t_vertex *v2)
{
	t_path 				*elem;

	elem = path_new();
	elem->curr_v = v1;
	if (v2)
		elem->prev_v = v2;
	if (elem != NULL)
	{
		elem->next_p = *dst;
		if (path_len(dst) > 2)
			elem->next_p->prev_p = elem;
		elem->prev_p = NULL;
		*dst = elem;
	}
}

void					path_add(t_path **dst, t_vertex *elem, t_vertex *prev)
{
	t_path				*p;
	t_path				*tmp;

	p = path_new();
	p->curr_v = elem;
	if (prev)
		p->prev_v = prev;
	path_pback(dst, p);
}
