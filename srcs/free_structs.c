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

void				edge_free(t_edge **edge)
{
	t_edge			*p;
	t_edge			*next;

	p = *edge;
	while (p)
	{
		next = p->next;
		ft_strdel(&p->v1);
		ft_strdel(&p->v2);
		free(p);
		p = next;
	}
	*edge = NULL;
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
	t_vertex		*next;

	while (ver)
	{
		next = ver->next;
		ft_strdel(&ver->name);
		while (ver->adj)
		{

			ver->adj = ver->adj->next;
		}
		free(ver);
		ver = next;
	}
}
