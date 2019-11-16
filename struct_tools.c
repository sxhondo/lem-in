#include "lem_in.h"

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
