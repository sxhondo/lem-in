#include "lem_in.h"

static int			all_finished(t_ants **ants)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos)
			return (0);
		a = a->next;
	}
	return (1);
}


static void			display_moves(t_ants **ants, t_vertex **ver)
{
	t_ants			*an;

	an = *ants;
	while (an)
	{
		if (an->pos && an->pos->node > 0)
			ft_printf("{red}L%d-{green}%s{eoc} ",
				an->id, find_ver_by_index(ver, an->pos->node)->name);
		an = an->next;
	}
	ft_printf("\n");
}

static void			push_new(t_ants **ants)
{
	int 			i;
	int 			new_id;
	t_ants			*a;

	i = 0;
	new_id = 1;
	a = *ants;
	while (a)
	{
		if (a->path == i && a->pos && a->pos->node == 0)
		{
			a->pos = a->pos->next;
			a->id += new_id;
			new_id++;
			i++;
		}
		a = a->next;
	}
}

static int			update(t_ants **ants)
{
	t_ants			*a;
	t_list			*l;

	a = *ants;
	while (a)
	{
		if (a->pos && a->pos->node != 0)
			a->pos = a->pos->next;
		a = a->next;
	}

}

void 				mover(t_vertex **ver, t_ants **ants)
{


	push_new(ants);
//	display_moves(ants, ver);
	ants_print(ants, ver);
/*
	while (!all_finished(ants))
	{
		update(ants);
		push_new(ants);
		display_moves(ants, ver);
	}
*/
}