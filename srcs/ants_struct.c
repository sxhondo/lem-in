/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:04:11 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:04:12 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ants_push_back(t_ants **dst, t_ants *ant)
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

t_ants			*ant_init(int id)
{
	t_ants		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	tmp->id = id;
	tmp->path = -1;
	return (tmp);
}

void 			print_ants_per_paths(t_ants **ants, int paths)
{
	t_ants 		*a;
	int 		i = 0;
	int 		counter = 0;

	while (i <= paths)
	{
		a = *ants;
		while (a)
		{
			if (a->path == i)
				counter++;
			a = a->next;
		}
		ft_printf("%d on path [%d]\n", counter, i);
		i++;
		counter = 0;
	}
}

int				ants_per_path(t_ants **ants, int path)
{
	t_ants		*a;
	int			r;

	r = 0;
	a = *ants;
	while (a)
	{
		if (a->path == path)
			r++;
		a = a->next;
	}
	return (r);
}

t_list			*get_i_paths(t_list **paths, int value)
{
	t_list		*l;

	l = *paths;
	while (l && value--)
		l = l->next;
	return (l);
}
