#include "lem_in.h"

void				steps_free(t_steps **steps)
{
	t_steps			*a;
	t_steps			*next;

	a = *steps;
	while (a)
	{
		next = a->next;
		free(a->ids);
		free(a);
		a = next;
	}
	a = NULL;
}

void				print_steps(t_steps **steps, int amount)
{
	int 			i;
	t_steps			*e;

	e = *steps;
	while (e)
	{
		i = -1;
		while (++i < amount)
			ft_printf("%d ", e->ids[i]);
		e = e->next;
		ft_printf("\n");
	}
}

static void			push_back_steps(t_steps **dst, t_steps *node)
{
	t_steps		*e;

	e = *dst;
	if (!*dst)
		*dst = node;
	else
	{
		while (e->next)
			e = e->next;
		e->next = node;
		node->next = NULL;
	}
}

void				fill_steps(t_steps **dst, t_ants **ants, int amount)
{
	t_ants			*a;
	t_steps			*n;

	if (!(n = ft_memalloc(sizeof(t_steps))))
	{
		put_error(12, 0, NULL);
		return ;
	}
	n->ids = ft_new_array(amount, 0);
	a = *ants;
	while (a)
	{
		n->ids[a->id - 1] = a->pos;
		a = a->next;
	}
	push_back_steps(dst, n);
}
