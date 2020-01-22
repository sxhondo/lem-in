/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_mover.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:05:55 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:06:12 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			all_finished(t_ants **ants)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos->curr_v->mod != 2)
			return (0);
		a = a->next;
	}
	return (1);
}

static int			no_one_next(t_ants **ants, char *next)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (ft_strequ(a->pos->curr_v->name, next))
			return (0);
		a = a->next;
	}
	return (1);
}

static void			push_turns(t_vec **turns, char *id, char *name)
{
	char			l;
	char			d;
	char			sp;
	int				i;

	l = 'L';
	d = '-';
	sp = ' ';
	ft_vec_add(turns, &l);
	i = -1;
	while (id[++i])
		ft_vec_add(turns, &id[i]);
	free(id);
	ft_vec_add(turns, &d);
	i = -1;
	while (name[++i])
		ft_vec_add(turns, &name[i]);
	ft_vec_add(turns, &sp);
}

static int			update(t_ants **ants, int id, t_vec *turns)
{
	t_ants			*a;
	char			n;

	n = '\n';
	a = *ants;
	while (a)
	{
		if (a->pos->next_p)
		{
			if (a->pos->next_p->curr_v->mod & END)
			{
				a->pos = a->pos->next_p;
				push_turns(&turns, ft_itoa(a->id), a->pos->curr_v->name);
			}
			else if (no_one_next(ants, a->pos->next_p->curr_v->name))
			{
				a->pos = a->pos->next_p;
				push_turns(&turns, ft_itoa(a->id), a->pos->curr_v->name);
			}
		}
		a = a->next;
	}
	ft_vec_add(&turns, &n);
	return (id);
}

void				mover(t_ants *ants, unsigned flag)
{
	int				id;
	t_vec			*turns;

	id = 0;
	if (!(turns = ft_vec_init(1, sizeof(char))))
		put_error("cannot allocate memory", 0);
	while (!all_finished(&ants))
		id = update(&ants, id, turns);
	if (!(ft_vec_resize(&turns)))
	{
		ft_vec_del(&turns);
		put_error("cannot allocate memory", 0);
	}
	if (!(flag & NO_OUT))
		write(1, turns->data, turns->total);
	if (flag & NL)
		count_print_nl(turns);
	ft_vec_del(&turns);
}
