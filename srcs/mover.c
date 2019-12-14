#include "lem_in.h"

static int			all_finished(t_ants **ants, int last)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos && a->pos->node != last)
			return (0);
		a = a->next;
	}
	return (1);
}


static void			display_moves(t_ants **ants, t_vertex **ver, unsigned flags)
{
	t_ants			*an;

	an = *ants;
	while (an)
	{
		if (an->pos && an->pos->node > 0)
		{
			if (flags & COLORS)
				ft_printf("{red}L%d-{blue}%s{eoc} ",
					 	 an->id, find_ver_by_index(ver, an->pos->node)->name);
			else
				ft_printf("L%d-%s ",
						  an->id, find_ver_by_index(ver, an->pos->node)->name);
		}
		an = an->next;
	}
}
/*
static int			push_new(t_ants **ants, int new_id)
{
	int 			i;
	int 			tmp;
	t_ants			*a;

	tmp = 0;
	a = *ants;
	while (a)
	{
		i = a->super_way ? 0 : tmp;
		if (a->path == i && a->pos && a->pos->node == 0)
		{
			a->pos = a->pos->next;
			a->id = new_id;
			new_id++;
			tmp++;
		}
		a = a->next;
	}
	return (new_id);
}
*/

static int 			no_one_next(t_ants **ants, int pos, int super_way)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (super_way)
			return (0);
		else if (a->pos && a->pos->node == pos)
			return (1);
		a = a->next;
	}
	return (0);
}

static int			push_new(t_ants **ants, int new_id)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos && a->pos->node == 0 && a->pos->next
			&& !(no_one_next(ants, a->pos->next->node, a->super_way)))
		{
			a->pos = a->pos->next;
			a->id = new_id;
			new_id++;
		}
		a = a->next;
	}
	return (new_id);
}

static void			update(t_ants **ants)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos && a->pos->node != 0)
			a->pos = a->pos->next;
		a = a->next;
	}
}

void 				mover(t_vertex **ver, t_ants **ants, unsigned flags)
{
	int 			id;

	id = push_new(ants, 1);
	display_moves(ants, ver, flags);
	while (!all_finished(ants, vertex_len(ver) - 1))
	{
		update(ants);
		id = push_new(ants, id);
		ft_printf("\n");
		display_moves(ants, ver, flags);
	}
	ft_printf("\n");
}