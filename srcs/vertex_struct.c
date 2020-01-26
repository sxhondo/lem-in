/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:46:30 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:46:33 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertex				*find_vertex(t_vertex *v, char *name)
{
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (NULL);
}

int					vertex_len(t_vertex **ver)
{
	int				i;
	t_vertex		*v;

	i = 0;
	v = *ver;
	while (v)
	{
		i++;
		v = v->next;
	}
	return (i);
}

void				vertex_push_back(t_vertex **dst, t_vertex *elem)
{
	t_vertex		*tmp;

	tmp = *dst;
	if (!*dst)
		*dst = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
	}
}

void				vertex_add(t_structs *structs, t_info *inf, int x, int y)
{
	t_vertex		*elem;

	if (!(elem = ft_memalloc(sizeof(t_vertex))))
	{
		put_error("cannot allocate memory", 0);
		return ;
	}
	if (!(elem->name = ft_strdup(inf->name)))
	{
		put_error("cannot allocate memory", 0);
		return ;
	}
	elem->x = x;
	elem->y = y;
	elem->on = 1;
	elem->mod = inf->mod;
	vertex_push_back((t_vertex **)&structs->ver, elem);
}