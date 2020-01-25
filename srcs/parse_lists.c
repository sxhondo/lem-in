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

static void				check_duplicate_vertex(t_vertex **ver)
{
	t_vertex			*i;
	t_vertex			*j;
	int					err;

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

static void				check_non_exst_ver(t_vertex **ver, t_edge **edge)
{
	t_vertex			*v;
	t_edge				*e;
	int					i;
	int					j;

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

static t_vertex			*copy_ver(t_vertex *ver)
{
	t_vertex			*d;
	t_vertex			*v;

	d = NULL;
	while (ver)
	{
		if (!(v = ft_memalloc(sizeof(t_vertex))))
			put_error("cannot allocate memory", 0);
		else
		{
			if (!(v->name = ft_strdup(ver->name)))
				put_error("cannot allocate memory", 0);
			v->i = ver->i;
			v->mod = ver->mod;
			vertex_push_back(&d, v);
			ver = ver->next;
		}
	}
	return (d);
}

static t_edge			*copy_edge(t_edge *edge)
{
	t_edge				*d;
	t_edge				*n;

	d = NULL;
	while (edge)
	{
		if (!(n = ft_memalloc(sizeof(t_edge))))
			put_error("cannot allocate memory", 0);
		else
		{
			if (!(n->tmp_name1 = ft_strdup(edge->v1->name)))
				put_error("cannot allocate memory", 0);
			if (!(n->tmp_name2 = ft_strdup(edge->v2->name)))
				put_error("cannot allocate memory", 0);
			n->del = 0;
			n->on = 1;
			edge_push_back(&d, n);
			edge = edge->next;
		}
	}
	return (d);
}

void					parse_lists(t_structs *structs)
{
	if (!structs->edge)
		put_error("no links given", 0);
	update_indexes(structs->ver);
	vertex_print(structs->ver);
	exit(0);	
	check_duplicate_vertex((t_vertex **)&structs->ver);
	check_non_exst_ver((t_vertex **)&structs->ver, (t_edge **)&structs->edge);
	link_edges_to_vertex((t_vertex **)&structs->ver, structs->edge);
	structs->cv = copy_ver(structs->ver);
	structs->ce = copy_edge(structs->edge);
	link_edges_to_vertex((t_vertex **)&structs->cv, structs->ce);
	update_indexes(structs->cv);
	structs->a_set = NULL;
	structs->b_set = NULL;
}
