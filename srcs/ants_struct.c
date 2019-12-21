#include "lem_in.h"

void			ants_push_back(t_ants **dst, t_ants *ant)
{
	t_ants		*a;

	a = *dst;
	if (!*dst)
		*dst = ant;
	else
	{
		while (a->next)
			a = a->next;
		a->next = ant;
		ant->next = NULL;
	}
}

t_ants			*ant_init(int id, int pos)
{
	t_ants		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	tmp->id = id;
	tmp->path = -1;
	return (tmp);
}

int 				ants_per_room(t_ants **ants, int path)
{
	t_ants			*a;
	int 			r;

	r = 0;
	a = *ants;
	while (a)
	{
		if (a->path == path)
			r++;
		a = a->next;
	}
	return (r);
}

t_list				*get_i_paths(t_list **paths, int value)
{
	t_list			*l;

	l = *paths;
	while (l && value--)
		l = l->next;
	return (l);
}

