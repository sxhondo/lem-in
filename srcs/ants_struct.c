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

t_ants			*ant_init(void)
{
	t_ants		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	tmp->path = -1;
	return (tmp);
}

int				ants_per_path(t_ants *ants, int path)
{
	int			count;

	count = 0;
	while (ants)
	{
		if (ants->path == path)
			count++;
		ants = ants->next;
	}
	return (count);
}
