/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:59:54 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:59:55 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int						path_len(t_path *dst)
{
	int					i;

	i = 0;
	while (dst)
	{
		dst = dst->next_p;
		i++;
	}
	return (i);
}

void					path_push(t_path **dst, t_path *elem)
{
	if (elem != NULL)
	{
		elem->next_p = *dst;
		if (elem->next_p)
			elem->next_p->prev_p = elem;
		elem->prev_p = NULL;
		*dst = elem;
	}
}

t_path					*path_init(t_vertex *curr)
{
	t_path				*p;

	if (!(p = ft_memalloc(sizeof(t_path))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	p->curr_v = curr;
	return (p);
}
