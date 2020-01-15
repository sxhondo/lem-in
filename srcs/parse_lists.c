/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:33:15 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:33:16 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_duplicate_vertex(t_vertex **ver)
{
	t_vertex	*i;
	t_vertex	*j;
	int			err;

	i = *ver;
	while (i)
	{
		err = 0;
		j = *ver;
		while (j)
		{
			if (ft_strequ(j->name, i->name))
				err++;
			j = j->next;
		}
		if (err > 1)
			put_error("duplicated room names", 0);
		i = i->next;
	}
}

static void		check_non_existing_vertex(t_vertex **ver, t_edge **edge)
{
	t_vertex	*v;
	t_edge		*e;
	int			i;
	int			j;

	e = *edge;
	while (e)
	{
		i = 0;
		j = 0;
		v = *ver;
		while (v)
		{
			if (ft_strequ(e->tmp_name1, v->name))
				i++;
			if (ft_strequ(e->tmp_name2, v->name))
				j++;
			v = v->next;
		}
		if (i == 0 || j == 0)
			put_error("room name does not exist", 0);
		e = e->next;
	}
}

static void		link_edges_to_vertex(t_vertex **ver, t_edge **edge)
{
	t_edge		*e;

	e = *edge;
	while (e)
	{
		e->v1 = find_ver_by_name(ver, e->tmp_name1);
		e->v2 = find_ver_by_name(ver, e->tmp_name2);
		ft_strdel(&e->tmp_name1);
		ft_strdel(&e->tmp_name2);
		e = e->next;
	}
}

void			parse_lists(t_vertex **ver, t_edge **edge)
{
	if (!*edge)
		put_error("no links given", 0);
	check_duplicate_vertex(ver);
	check_non_existing_vertex(ver, edge);
	link_edges_to_vertex(ver, edge);
	update_indexes(*ver);
//	put_to_end(ver);
//	put_to_begin(ver);
}
