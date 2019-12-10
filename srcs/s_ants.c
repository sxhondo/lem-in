#include "lem_in.h"

void			free_ants(t_ants **s)
{
	t_ants			*a;
	t_ants			*next;

	a = *s;
	while (a)
	{
		next = a->next;
		free(a);
		a = next;
	}
	a = NULL;
}

static void		push_back(t_ants **dst, t_ants *ant)
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

static t_ants	*init_ant(int id, int pos)
{
	t_ants		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	tmp->pos = pos;
	tmp->id = id;
	return (tmp);
}

t_ants 			*spawn_ants(int amount)
{
	int 	i;
	t_ants	*node;
	t_ants	*ants = NULL;


	i = 1;
	while (amount--)
	{
		node = init_ant(i, 0);
		push_back(&ants, node);
		i++;
	}
	return (ants);
}
