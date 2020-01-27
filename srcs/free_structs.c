/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:13:29 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:13:30 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ants_free(t_ants **s)
{
	t_ants			*a;
	t_ants			*next;

	a = *s;
	while (a)
	{
		next = a->next;
		free(a);
		a = next;
	}
	*s = NULL;
}

void				edge_free(t_edge *edge)
{
	t_edge			*next;

	while (edge)
	{
		next = edge->next;
		ft_strdel(&edge->v1);
		ft_strdel(&edge->v2);
		free(edge);
		edge = next;
	}
}

void				path_free(t_path **s)
{
	t_path			*p;
	t_path			*next;

	p = *s;
	while (p)
	{
		next = p->next_p;
		free(p);
		p = next;
	}
	*s = NULL;
}

void				free_list(t_list **tab)
{
	t_list			*lst;
	t_list			*next;
	t_path			*ptr;

	lst = *tab;
	while (lst)
	{
		next = lst->next;
		ptr = lst->content;
		path_free(&ptr);
		free(lst);
		lst = next;
	}
	*tab = NULL;
}

void				vertex_free(t_vertex *ver)
{
	t_list 			*p;
	t_list 			*p_next;
	t_vertex		*next;

	while (ver)
	{
		next = ver->next;
		ft_strdel(&ver->name);
		while (ver->adj)
		{
			p = ver->adj->next;
			free(ver->adj);
			ver->adj = p;
		}
		free(ver);
		ver = next;
	}
}
