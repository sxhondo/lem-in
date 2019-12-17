#include "lem_in.h"

static int          all_finished(t_ants **ants)
{
    t_ants          *a;

    a = *ants;
    while (a)
    {
        if (a->pos->curr_v->mod != 2)
            return (0);
        a = a->next;
    }
    return (1);
}

static int          no_one_next(t_ants **ants, char *next)
{
    t_ants          *a;

    a = *ants;
    while (a)
    {
        if (ft_strequ(a->pos->curr_v->name, next))
        {
            return (0);
        }
        a = a->next;
    }
    return (1);
}

static int          update(t_ants **ants, int id)
{
    t_ants          *a;

    a = *ants;
    while (a)
    {
        if (a->pos->next_p && a->pos->next_p->curr_v->mod == 2)
        {
            a->pos = a->pos->next_p;
            ft_printf("L%d-%s ", a->id, a->pos->curr_v->name);
        }
        if (a->pos->next_p &&
            no_one_next(ants, a->pos->next_p->curr_v->name))
        {
            if (a->id == 0)
            {
                a->id = id;
                id++;
            }
            a->pos = a->pos->next_p;
            ft_printf("L%d-%s ", a->id, a->pos->curr_v->name);
        }
        a = a->next;
    }
    ft_printf("\n");
    return (id);
}

void 				mover(t_ants **ants, unsigned flags)
{
	int 			id;

    id = 1;
    while (!all_finished(ants))
    {
        id = update(ants, id);
        if (flags & DEBUG)
            ants_print(ants);
    }
}
