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

static void				check_duplicate_vertex(t_vertex *ver)
{
	t_vertex			*i;
	t_vertex			*j;
	int					err;

	i = ver;
	while (i)
	{
		err = 0;
		j = ver;
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

static t_list			*establish_connection(char *curr, t_vertex *ver,
																t_edge *edge)
{
	t_list				*n;
	t_list				*adj;
	t_vertex			*tmp;

	adj = NULL;
	while (edge)
	{
		if (ft_strequ(curr, edge->v1))
		{
			if ((tmp = find_vertex(ver, edge->v2)) == NULL)
				put_error("room name does not exist", 0);
			n = ft_lstnew(&tmp->i, sizeof(int));
			ft_lstadd(&adj, n);
		}
		else if (ft_strequ(curr, edge->v2))
		{
			if ((tmp = find_vertex(ver, edge->v1)) == NULL)
				put_error("room name does not exist", 0);
			n = ft_lstnew(&tmp->i, sizeof(int));
			ft_lstadd(&adj, n);
		}
		edge = edge->next;
	}
	return (adj);
}

void					create_adjacency_list(t_vertex *ver, t_edge *edge)
{
	t_vertex			*tmp;
	int 				i;

	i = 0;
	check_duplicate_vertex(ver);
	tmp = ver;
	tmp->i = i;
	while ((tmp = tmp->next))
		tmp->i = ++i;
	tmp = ver;
	while (tmp)
	{
		tmp->adj = establish_connection(tmp->name, ver, edge);
		tmp = tmp->next;
	}
	exit(0);
}

