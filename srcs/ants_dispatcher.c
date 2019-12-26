/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:01:12 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:01:13 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_super_way(t_list **paths)
{
	t_list		*l;
	t_path		*p;

	l = *paths;
	while (l)
	{
		p = l->content;
		if (path_len(&p) == 2)
			return (1);
		l = l->next;
	}
	return (0);
}

static void		set_super_flag(t_ants **ants)
{
	t_ants		*a;

	a = *ants;
	while (a)
	{
		a->path = 0;
		a->super_way = 1;
		a = a->next;
	}
}

static void		link_nodes(t_ants **ants, t_list **paths)
{
	t_ants		*a;
	t_list		*tmp;

	a = *ants;
	while (a)
	{
		tmp = get_i_paths(paths, a->path);
		a->pos = get_i_path_node((t_path **)&tmp->content, a->indx);
		a = a->next;
	}
}

static void		dispatcher(int amount, t_list **paths, t_ants **ants, int i)
{
	int			p_len;
	int			p_next_len;
	int			a;
	t_list		*tmp;
	t_ants		*an;

	an = *ants;
	an->path = 0;
	an = an->next;
	amount -= 1;
	while (amount--)
	{
		p_len = path_len((t_path **)&get_i_paths(paths, i)->content);
		a = ants_per_room(ants, i);
		if (!(tmp = get_i_paths(paths, i + 1)))
		{
			i = -1;
			tmp = get_i_paths(paths, i + 1);
		}
		p_next_len = path_len((t_path **)&tmp->content);
		an->path = (p_len + a) <= p_next_len ? i : ++i;
		an = an->next;
	}
}

t_ants			*spawn_ants(int amount, t_list **ways)
{
	int			i;
	int			tmp;
	t_ants		*node;
	t_ants		*ants;

	ants = NULL;
	i = 1;
	tmp = amount;
	while (tmp--)
	{
		node = ant_init(0);
		ants_push_back(&ants, node);
		i++;
	}
	if (is_super_way(ways))
		set_super_flag(&ants);
	else
		dispatcher(amount, ways, &ants, 0);
	link_nodes(&ants, ways);
	return (ants);
}
