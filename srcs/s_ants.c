#include "lem_in.h"

static void		ant_push_back(t_ants **dst, t_ants *ant)
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
		return (put_error(12, 0, NULL));
	tmp->pos = pos;
	tmp->id = id;
	return (tmp);
}

void			print_ants(t_ants **ants, t_vertix **ver, t_steps **steps, int last, int amount)
{
	t_ants		*p;
	int 		i;

	i = 0;
	p = *ants;
	while (p)
	{
		if (p->pos != 0 && p->pos != -1)
		{
			ft_printf("L%d-%s ", p->id, get_i_ver(ver, p->pos));
		}
		if (p->pos == last)
			p->pos = -1;
		p = p->next;
	}
	fill_steps(steps, ants, amount);
	ft_printf("\n");
}

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

t_ants 			*spawn_ants(int amount)
{
	int 	i;
	t_ants	*ants = NULL;

	i = 1;
	while (amount--)
	{
		ant_push_back(&ants, init_ant(i, 0));
		i++;
	}
	return (ants);
}
