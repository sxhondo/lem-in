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

int 			find_min_value(int *cost, int len)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < len)
	{
		j = -1;
		while (++j < len && cost[i] <= cost[j])
			;
		if (j == len)
		{
			free(cost);
			return (i);
		}
		i++;
	}
	free(cost);
	return (-1);
}

static int 		get_min_path(t_ants **ants, t_list **ways)
{
	t_list 		*w;
	t_path 		*p;
	int 		*cost;
	int 		i;

 	i = 0;
	w = *ways;
	if (!(cost = ft_new_array(ft_lstlen(ways), -1)))
		put_error("cannot allocate memory", 0);
	else
	{
		while (w)
		{
			p = w->content;
			cost[i] = (path_len(&p) - 1) + ants_per_path(ants, i);
			w = w->next;
			i++;
		}
	}
//	print_arr(cost, ft_lstlen(ways));
	return (find_min_value(cost, ft_lstlen(ways)));
}

static void 	dispatcher(int amount, t_list **ways, t_ants **ants)
{
	t_ants 		*a;
	int 		min;
	int 		id;

	id = 1;
	a = *ants;
	while (a)
	{
		min = get_min_path(ants, ways);
		a->path = min;
		a->id = id++;
 		a = a->next;
	}

}

static void 	set_ants_on_path(t_ants *ants, t_list **ways)
{
	t_list		*tmp;

	while (ants)
	{
		tmp = *ways;
		while (ants->path)
		{
			tmp = tmp->next;
			ants->path--;
		}
		ants->pos = tmp->content;
		ants = ants->next;
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
//	ants_print(&ants);
	if (is_super_way(ways))
		set_super_flag(&ants);
	else
		dispatcher(amount, ways, &ants);
	set_ants_on_path(ants, ways);
	return (ants);
}
