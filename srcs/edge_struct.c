/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:05:12 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:05:13 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void						edge_push_back(t_edge **dst, t_edge *elem)
{
	t_edge					*tmp;

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

t_edge						*edge_init(char *e1, char *e2)
{
	t_edge					*edge;

	if (!(edge = ft_memalloc(sizeof(t_edge))))
	{
		put_error("cannot alocate memory", 0);
		return (NULL);
	}
	edge->v1 = ft_strdup(e1);
	edge->v2 = ft_strdup(e2);
	if (edge->v1 == NULL || edge->v2 == NULL)
		put_error("cannot alocate memory", 0);
	return (edge);
}

void						edge_add(t_structs *structs, t_info *inf)
{
	int						i;
	char					*v1;
	char					*v2;
	char					*name;
	t_edge					*elem;

	name = inf->name;
	if (inf->mod)
		put_error("link cannot be room-modificator", inf->lc);
	i = cut_after_symbol(name, &v1, '-');
	name += i;
	if (!*name || !(*name + 1))
		put_error("link not well formatted", inf->lc);
	name += 1;
	if (!(v2 = ft_strdup(name)))
		put_error("cannot alocate memory", 0);
	elem = edge_init(v1, v2);
	edge_push_back((t_edge **)&structs->edge, elem);
	ft_strdel(&v1);
	ft_strdel(&v2);
}

//t_edge						*find_edge(t_edge **edge, char *f, char *to)
//{
//	t_edge					*e;
//
//	e = *edge;
//	while (e)
//	{
//		if ((ft_strequ(e->v1->name, f) && ft_strequ(e->v2->name, to)))
//			return (e);
//		e = e->next;
//	}
//	return (NULL);
//}
