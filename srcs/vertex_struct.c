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

t_vertex			*find_ver_by_name(t_vertex **ver, char *name)
{
	t_vertex		*v;

	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (NULL);
}

void 				vertex_insert(t_vertex **ver, t_vertex *elem)
{
	t_vertex		*v;
	t_vertex		*next;

	v = *ver;
	if (v == NULL)
	{
		*ver = elem;
		return ;
	}
	next = v->next;
	v->next = elem;
	elem->next = next;
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
	elem->mod = inf->mod;
	elem->div = 0;
	elem->vis = 0;
	vertex_push_back((t_vertex **)&structs->ver, elem);
}

t_vertex			*vertex_dupl(t_vertex **ver, char *name, unsigned div)
{
	t_vertex		*elem;

	if (!(elem = ft_memalloc(sizeof(t_vertex))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	if (!(elem->name = ft_strdup(name)))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	elem->div = div;
	elem->vis = 0;
	vertex_push_back(ver, elem);
}

t_vertex			*vertex_duplic(t_vertex **ver, t_vertex *v)
{
	t_vertex		*elem;

	if (!(elem = ft_memalloc(sizeof(t_vertex))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	if (!(elem->name = ft_strdup(v->name)))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	elem->div = v->div;
	elem->vis = 0;
	elem->mod = v->mod;
	elem->i = v->i;
	vertex_push_back(ver, elem);
}