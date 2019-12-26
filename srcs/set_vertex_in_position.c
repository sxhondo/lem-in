/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vertex_in_position.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:00:52 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:00:52 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vertex			*iter_to_last(t_vertex **ver)
{
	t_vertex			*ptr;

	ptr = *ver;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void				first_swap(t_vertex **ver)
{
	t_vertex			*v;
	t_vertex			*last;
	t_vertex			*next;

	last = iter_to_last(ver);
	v = *ver;
	next = v->next;
	v->next = NULL;
	last->next = v;
	*ver = next;
}

static void				swap_lst(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*last;
	t_vertex			*prev;
	t_vertex			*next;

	p = *ver;
	while (p)
	{
		if (p->next->mod == 2)
		{
			prev = p;
			next = p->next->next;
			last = iter_to_last(ver);
			last->next = p->next;
			p->next->next = NULL;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}

void					put_to_end(t_vertex **ver)
{
	t_vertex			*v;
	t_vertex			*last;
	t_vertex			*next;

	last = iter_to_last(ver);
	if (last->mod == 2)
		return ;
	v = *ver;
	if (vertex_len(ver) == 2)
	{
		next = v->next;
		v->next = NULL;
		next->next = v;
		*ver = next;
	}
	else if (v->mod == 2)
		return (first_swap(ver));
	else
		swap_lst(ver);
}

void					put_to_begin(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*prev;
	t_vertex			*next;

	if ((*ver)->mod == 1)
		return ;
	p = *ver;
	while (p)
	{
		if (p->next->mod == 1)
		{
			prev = p;
			next = p->next->next;
			p->next->next = *ver;
			(*ver) = p->next;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}
