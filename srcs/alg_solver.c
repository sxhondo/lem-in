/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:35:57 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:35:58 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


static t_edge		*save_original_graph_edges(t_edge *orig, t_vertex **v)
{
	t_edge			*save;
	t_edge			*tmp;

	save = NULL;
	while (orig)
	{
		if (!(tmp = ft_memalloc(sizeof(t_edge))))
		{
			put_error("cannot allocate memory", 0);
			return (NULL);
		}
		tmp->v1 = find_ver_by_name(v, orig->v1->name);
		tmp->v2 = find_ver_by_name(v, orig->v2->name);
		tmp->del = 0;
		tmp->cost = 0;
		edge_push_back(&save, tmp);
		orig = orig->next;
	}
	return (save);
}

static t_vertex		*save_original_graph_ver(t_vertex *ver)
{
	t_vertex		*save;

	save = NULL;
	while (ver)
	{
		vertex_duplic(&save, ver);
		ver = ver->next;
	}
	return (save);
}

static int 			find_sf(t_vertex *ver, int sf)
{

	while (ver)
	{
		if (ver->mod == sf)
			return (ver->i);
		ver = ver->next;
	}
	return (-1);
}

static int 			total_actions(t_list *set)
{
	t_path			*r;
	int 			tmp;

	tmp = 0;
	while (set)
	{
		r = set->content;
		tmp += path_len(&r) - 1;
		set = set->next;
	}
	return (tmp);

}

static int 			get_cf(t_list *set, int amount)
{
	int 			tmp;
	int 			len;

	len = ft_lstlen(&set);
	tmp = total_actions(set);
	tmp += amount;
	if (tmp % len)
		tmp--;
	tmp = tmp / len;
//	ft_printf("CF: %d\n", tmp);
	return (tmp);
}

static t_list 		*collect_set(t_edge *ce, t_vertex *cv, int max_paths)
{
	t_list			*br_set = NULL;
	t_path			*route;
	int 			s, f;

	s = find_sf(cv, START);
	f = find_sf(cv, END);
	while ((route = breadth_first_search(&ce, &cv, s, f)) && max_paths--)
	{
		delete_route(&route, &ce);
		add_path_to_lst(&br_set, route);
	}
	reset_map(&ce);
	return (br_set);
}

int 				recalc(t_list *ways)
{
	int 			a;
	int 			len;
	t_path			*p;

	a = 0;
	len = ft_lstlen(&ways);
	while (ways)
	{
		p = ways->content;
		a += path_len(&p) - 2;
		ways = ways->next;
	}
	return (a);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	t_list 			*ex_set = NULL;
	t_path			*route;
	t_edge			*copy_e;
	t_vertex		*copy_v;
	int 			s, f;


	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	if (!(route = breadth_first_search(edge, ver, s, f)))
		put_error("no possible solution", 0);

	ex_set = update_graph(edge, ver, route, ex_set);

	copy_v = save_original_graph_ver(*ver);
	copy_e = save_original_graph_edges(*edge, &copy_v);

	int 	a = 0;
	int 	max_paths;
	t_list	*tset = NULL;
	t_list	*oset = NULL;

	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	while ((route = breadth_first_search(edge, ver, s, f)))
	{
		update_graph(edge, ver, route, ex_set);
		put_paths_on_map(&copy_e, &ex_set);
		max_paths = ft_lstlen(&ex_set);
		tset = collect_set(copy_e, copy_v, max_paths);
		if (oset != NULL)
		{
			int ts = get_cf(tset, ants);
			int os = get_cf(oset, ants);
			if (ts > os)
			{
				return (oset);
			}
//			ft_printf("tes: %d tos: %d\n", total_actions(tset), total_actions(oset));
//			ft_printf("ts: %d os: %d\n---\n", ts, os);

		}
		oset = tset;
	}
	edge_free(&copy_e);
	vertex_free(ver);
	return (tset);
}