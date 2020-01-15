/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:52:39 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:52:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			edge_print(t_edge *e)
{
	ft_printf("{blue}------edges----------{eoc}\n");
	while (e)
	{
		ft_printf("{blue}%s[%d] ", e->v1->name, e->v1->i);
		if (e->v1->div & IN)
			ft_printf("(%s)", "in");
		if (e->v1->div & OUT)
			ft_printf("(%s)", "out");
		ft_printf("-> %s[%d]", e->v2->name, e->v2->i);
		if (e->v2->div & IN)
			ft_printf("(%s)", "in");
		if (e->v2->div & OUT)
			ft_printf("(%s)", "out");
		ft_printf("{eoc} del: %d co %d\n", e->del, e->cost);
		e = e->next;
	}
	ft_printf("\n");
}

void			path_print(t_path **path, char mode)
{
	t_path		*tmp;

	tmp = *path;
	if (mode == 'b')
	{
		while (tmp->next_p)
			tmp = tmp->next_p;
		ft_printf("[");
		while (tmp)
		{
			ft_printf("%s ", tmp->curr_v->name);
			tmp = tmp->prev_p;
		}
		ft_printf("]\n");
	}
	else
	{
		while (tmp)
		{
			ft_printf("%s ", tmp->curr_v->name);
			tmp = tmp->next_p;
		}
	}
}

void			ants_print(t_ants **ants)
{
	t_ants		*an;

	an = *ants;
	while (an)
	{
		ft_printf("{red}id:[%d]{eoc}\t", an->id);
		ft_printf(" {cyan}path: %d{eoc}\t", an->path);
		if (an->pos)
			ft_printf("{green} pos: %s{eoc}\n", an->pos->curr_v->name);
		else
			ft_printf("{magenta} finished! {eoc}\n");
		an = an->next;
	}
	ft_printf("\n");
}

void			vertex_print(t_vertex **ver)
{
	int			i;
	t_vertex	*p;

	i = 0;
	p = *ver;
	ft_printf("{red}------vertexes-------{eoc}\n");
	while (p)
	{
		ft_printf("[%d] ", p->i);
		if (p->mod == 1)
			ft_printf("{blue}%s {eoc}", p->name);
		else if (p->mod == 2)
			ft_printf("{red}%s {eoc}", p->name);
		else if (p->div)
		{
			ft_printf("{magenta}%s ", p->name);
			if (p->div & IN)
				ft_printf("(in)");
			else if (p->div & OUT)
				ft_printf("(out)");
			ft_printf("{eoc}");
		}
		else
			ft_printf("%s ", p->name);
		ft_printf("\n");
		p = p->next;
	}
}

void			print_queue(t_list *lst, void **ver)
{
	int			tmp;

	ft_printf("q: ");
	while (lst)
	{
		tmp = *((int *)lst->content);
		ft_printf("%s [%d] ", ((t_vertex *)ver[tmp])->name, tmp);
		lst = lst->next;
	}
	ft_printf("\n");
}
