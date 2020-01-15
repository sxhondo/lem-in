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

static int 			get_cf(t_list *set, int amount)
{
	int 			tmp;
	t_path 			*r;
	int 			len;

	len = ft_lstlen(&set);
	tmp = 0;
	while (set)
	{
		r = set->content;
		tmp += path_len(&r);
		set = set->next;
	}
	tmp += amount;
	tmp = tmp / len;
	return (tmp);
}
////
//static t_list 		*pick_best_set(t_edge **edge, void **vp, t_list **set, int len, int amount)
//{
//	t_path			*r;
//	t_list			*new;
//	t_list			*prev;
//	int 			sl;
//	int 			i;
//
//	new = NULL;
//	prev = NULL;
//	reset_map(edge, 0);
//	sl = ft_lstlen(set);
//	i = -1;
//	while (++i < sl)
//	{
//		put_paths_on_map(edge, set, i + 1);
//		while ((r = breadth_first_search(edge, vp, len)))
//		{
//			delete_route(&r, edge);
//			add_path_to_lst(&new, r);
//		}
//		if (prev != NULL)
//			if ((choose_set(new, prev, amount)))
//			{
//				new = prev;
//				break ;
//			}
//		prev = new;
//		new = NULL;
////		ways_print(&prev);
////		ft_printf("{green}%d{eoc}\n", get_cf(prev, amount));
//		reset_map(edge, 0);
//	}
//	free_list(set);
////	ft_printf("%d %d\n", i, sl);
////	ft_printf("{yellow}%d{eoc}", get_cf(prev, amount));
////	exit (0);
//	return (prev);
//}


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
		tmp->del = 1;
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

//static t_list		*get_excluding_set(t_edge **edge, t_vertex **ver, void **vp)
//{
//	int 			len;
//	t_path			*r;
//	t_list 			*set;
//
//	set = NULL;
//	len = vertex_len(ver);
//	while ((r = spf_algorithm(edge, vp, len)))
//	{
//		flip_route(&r, edge);
//		vp = update_graph(edge, ver, vp);
//		len = vertex_len(ver);
//		add_path_to_lst(&set, r);
//	}
//	edge_free(edge);
//	return (set);
//}

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

//static t_list		*get_excluding_set(t_edge **edge, t_vertex **ver, void **vp)
//{
//	int 			st[2];
//	int 			len;
//	t_path			*r;
//	t_list 			*set;
//
//	set = NULL;
//	len = vertex_len(ver);
//	vertex_print(ver);
////
////	exit (0);
////	while ((r = breadth_first_search(edge, ver, len)))
////	{
////		path_print(&r, 'f');
////		ft_printf("\n");
////		flip_route(&r, edge);
////		update_graph(edge, ver, vp);
////		vertex_print(ver);
////		len = vertex_len(ver);
////		add_path_to_lst(&set, r);
////	}
////	edge_free(edge);
////	return (set);
//}


static t_list		*get_excluding_set(t_edge **edge, t_vertex **ver)
{
	int 			st[2];
	int 			len;
	t_path			*r;
	t_list 			*set;
	int 			s, f;

	set = NULL;
	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	while ((r = breadth_first_search(edge, ver, s, f)))
	{
//		path_print(&r, 'f');
//		ft_printf("\n");
		flip_route(&r, edge);
		update_graph(edge, ver);
		add_path_to_lst(&set, r);
	}
	return (set);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	t_list 			*set;
	t_path			*route;
	t_edge			*copy_e;
	t_vertex		*copy_v;
	int 			s, f;

	set = NULL;
	s = find_sf(*ver, START);
	f = find_sf(*ver, END);

	if (!(route = breadth_first_search(edge, ver, s, f)))
		put_error("no possible solution", 0);
	if (path_len(&route) == 2)
	{
		add_path_to_lst(&set, route);
		return (set);
	}
	path_free(&route);
	copy_v = save_original_graph_ver(*ver);
	copy_e = save_original_graph_edges(*edge, &copy_v);

	set = get_excluding_set(edge, ver);
//	ways_print(&set);
	put_paths_on_map(&copy_e, &set);
	free_list(&set);
	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	while ((route = breadth_first_search(&copy_e, &copy_v, s, f)))
	{
		delete_route(&route, &copy_e);
		add_path_to_lst(&set, route);
	}
	return (set);
}
