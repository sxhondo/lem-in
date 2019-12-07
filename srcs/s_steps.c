#include "lem_in.h"

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
