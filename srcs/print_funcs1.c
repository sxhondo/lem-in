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
		ft_printf("%s {blue}-{eoc} %s\n", e->v1, e->v2);
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
		ft_printf(" {cyan}path: %d{eoc}\t\n", an->path);
		an = an->next;
	}
	ft_printf("\n");
}

void			adj_print(t_vertex *ver)
{
	t_list 		*p;
	ft_printf("{red}--adj--{eoc}\n");
	while (ver)
	{
		ft_printf("[%2d] ", ver->i);
		if (ver->mod == 1)
			ft_printf("{red}%3s {eoc}", ver->name);
		else if (ver->mod == 2)
			ft_printf("{red}%3s {eoc}", ver->name);
		else
			ft_printf("%3s {eoc}", ver->name);
		p = ver->adj;	
		while (p)
		{
			ft_printf("{blue}%3d ", *((int *)p->content));
			p = p->next;
		}
		ft_printf("{eoc}\n");
		ver = ver->next;
	}
}

void			vertex_print(t_vertex *ver)
{
	int			i;

	i = 0;
	ft_printf("{red}------vertexes-------{eoc}\n");
	while (ver)
	{
		ft_printf("[%2d] ", ver->i);
		if (ver->mod == 1)
			ft_printf("{blue}%3s{eoc}", ver->name);
		else if (ver->mod == 2)
			ft_printf("{red}%3s{eoc}", ver->name);
		else
			ft_printf("%3s", ver->name);
		ft_printf("\n");
		ver = ver->next;
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
