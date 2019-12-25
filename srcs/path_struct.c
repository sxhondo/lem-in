#include "lem_in.h"

t_path					*get_i_path_node(t_path **path, int value)
{
	t_path				*p;

	p = *path;
	while (p && value--)
		p = p->next_p;
	return (p);
}

int 					path_len(t_path **dst)
{
	t_path				*p;
	int 				i;

	i = 0;
	p = *dst;
	while (p)
	{
		p = p->next_p;
		i++;
	}
	return (i);
}

void					path_push(t_path **dst, t_path *elem)
{
	if (elem != NULL)
	{
		elem->next_p = *dst;
		if (elem->next_p)
			elem->next_p->prev_p = elem;
		elem->prev_p = NULL;
		*dst = elem;
	}
}

void 					path_push_back(t_path **dst, t_path *elem)
{
	t_path 				*tmp;

	tmp = *dst;
	if (!*dst)
	{
		*dst = elem;
		return ;
	}
	else
		while (tmp->next_p)
			tmp = tmp->next_p;
	tmp->next_p = elem;
	elem->prev_p = elem;
	elem->next_p = NULL;
}

t_path 					*path_init(t_vertex *curr)
{
	t_path 				*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	p->curr_v = curr;
	return (p);
}
