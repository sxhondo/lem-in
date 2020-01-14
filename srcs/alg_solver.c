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

//static int 			get_cf(t_list *set, int amount)
//{
//	int 			tmp;
//	t_path 			*r;
//	int 			len;
//
//	len = ft_lstlen(&set);
//	tmp = 0;
//	while (set)
//	{
//		r = set->content;
//		tmp += path_len(&r);
//		set = set->next;
//	}
//	tmp += amount;
//	tmp = tmp / len;
//	return (tmp);
//}
//
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

static t_list		*get_excluding_set(t_edge **edge, t_vertex **ver, void **vp, int len)
{
	t_path			*r;
	t_list 			*set;

	set = NULL;
	while ((r = spf_algorithm(edge, vp, len)))
	{
		flip_route(&r, edge);
//		divide_nodes(r, edge, ver, vp, len);
		add_path_to_lst(&set, r);
	}
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	void			**vp;
	int				len;
	t_list 			*set;
	t_path			*route;

	set = NULL;
	len = vertex_len(ver);
	vp = convert_ver_to_ptrs(ver, len);
	set_indexes_of_ver(edge, vp, len);
	if (!(route = get_cheapest_path(edge, vp, len)))
		put_error("no possible solution", 0);
	if (path_len(&route) == 2)
	{
		free (vp);
		add_path_to_lst(&set, route);
		return (set);
	}
	path_free(&route);
	set = get_excluding_set(edge, ver, vp, len);
//	return (pick_best_set(edge, vp, &set, len, ants));
}
