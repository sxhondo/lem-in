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

static int 		find_min_value(const int *cost, int len)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < len)
	{
		j = i;
		while (j < len)
		{
			if (cost[i] <= cost[j])
				j++;
			else
				break ;
		}
		if (j == len)
			return (i);
		i++;
	}
}

static t_path	*get_i_path(t_list *ways, int i)
{
	t_path		*tmp;

	while (ways->next && i--)
		ways = ways->next;
	tmp = ways->content;
	return (tmp);
}

static void 	linkage(t_ants *ants, t_list *ways, int *cost, int len)
{
	int 		i, j;

	i = 1;
	if (len == 0)
	{
		j = 0;
		while (ants)
		{
			ants->id = i++;
			ants->pos = get_i_path(ways, j++);
			ants = ants->next;
		}
		return ;
	}
	while (ants)
	{
		ants->id = i++;
		j = find_min_value(cost, len);
		ants->pos = get_i_path(ways, j);
		ants->path = j;
		cost[j] += ants_per_path(ants, j);
		ants = ants->next;
	}
}

static void 	dispatcher(t_list *ways, t_ants *ants)
{
	t_list		*w;
	int 		*cost;
	int 		len;
	int 		i;

	i = -1;
	len = ft_lstlen(&ways);
	cost = ft_new_array(len, 0);
	w = ways;
	while (++i < len)
	{
		cost[i] = path_len((t_path *)w->content) - 1;
		w = w->next;
	}
	linkage(ants, ways, cost, len);
	free(cost);
}

t_ants			*spawn_ants(int amount, t_list *ways)
{
	int			i;
	int			a;
	t_ants		*tmp;
	t_ants		*ants;

	ants = NULL;
	a = amount;
	while (a--)
	{
		tmp = ant_init();
		ants_push_back(&ants, tmp);
	}
	if (path_len(ways->content) != 2)
	{
		dispatcher(ways, ants);
		return (ants);
	}
	linkage(ants, ways, NULL, 0);
	return (ants);
}
