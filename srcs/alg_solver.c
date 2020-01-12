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

#include <stdio.h>
#include "lem_in.h"

static t_list		*mini_solution(t_path *route, t_list **ways, void **vp)
{
	add_path_to_lst(ways, route);
	free(vp);
	return (*ways);
}

//static t_list		*get_cross_set(t_edge **edge, void **vp, int len, int ants)
//{
//	t_path			*route;
//	t_list			*ways;
//
//	ways = NULL;
//	while ((route = get_cheapest_path(edge, vp, len)))
//	{
//		exclude_route(&route, edge);
//		cross_paths(route, &ways);
//		add_path_to_lst(&ways, route);
//	}
//	reset_map(edge, 0);
//	put_paths_on_map(edge, &ways);
//	while ((route = breadth_first_search(edge, vp, len)))
//	{
//		delete_route(&route, edge);
//		if (!(cross_paths(route, &ways)))
//			add_path_to_lst(&ways, route);
//	}
//	return (ways);
//}


static int 			get_cf(t_list **ways, t_path *route, int ants)
{
	int 			steps;
	int 			paths;
	int 			tmp;
	t_list			*l;

	paths = ft_lstlen(ways) ? ft_lstlen(ways) : 1;
	steps = 0;
	l = *ways;
	if (l)
	{
		while (l)
		{
			steps += path_len((t_path **)&l->content) - 1;
			l = l->next;
		}
		steps += path_len(&route) - 1;
	}
	else
		steps = path_len(&route) - 1;
	tmp = steps + ants;
	return (tmp % paths ? (tmp / paths) : (tmp / paths) - 1);

}

static t_list		*get_brute_set(t_edge **edge, void **vp, int len)
{
	t_path			*route;
	t_list			*ways;

	ways = NULL;
	reset_map(edge, 1);
	while ((route = breadth_first_search(edge, vp, len)))
	{
		delete_route(&route, edge);
		if (!(cross_paths(route, &ways)))
			add_path_to_lst(&ways, route);
	}
	return (ways);
}

static t_path		*augment_route(t_path **route, t_edge **edge, void **vp, int len)
{
	t_edge			*e;
	t_path			*augm;
	t_path			*r;
	int 			t;
	int 			n;

	t = path_len(route);
//	ft_printf("try path: \n");
//	path_print(route, 'f');
//	ft_printf("\n");
	r = *route;
	while (r)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->del = 1;
		if (!(augm = spf(edge, vp, len)))
		{
			e->del = 0;
			return (NULL);
		}
		else
		{
			n = path_len(&augm);
			if (n > t)
			{
				e->del = 0;
				path_free(route);
				return (augm);
			}
			else
				e->del = 0;
		}
		r = r->next_p;
	}
	return (NULL);
}

static t_list 		*get_spf_set(t_edge **edge, void **vp, int len)
{
	t_list			*cset;
	t_list			*bset;
	t_list 			*tmp;
	t_path			*route;


	bset = NULL;
	while ((route = breadth_first_search(edge, vp, len)))
	{
		delete_route(&route, edge);
		if (!(cross_paths(route, &bset)))
			add_path_to_lst(&bset, route);
		else
			path_free(&route);
	}
//	ways_print(&bset);
	reset_map(edge, 1);
	tmp = NULL;
	cset = NULL;
	while ((route = spf(edge, vp, len)))
	{
		exclude_route(&route, edge);
		add_path_to_lst(&tmp, route);
	}
	reset_map(edge, 0);
//	ways_print(&bset);
	put_paths_on_map(edge, &tmp);
	while ((route = breadth_first_search(edge, vp, len)))
	{
//		path_print(&route, 'f');
//		ft_printf("\n");
		delete_route(&route, edge);
		if (!(cross_paths(route, &cset)))
			add_path_to_lst(&cset, route);
		else
			path_free(&route);
	}
	free(vp);
	if (ft_lstlen(&cset) > ft_lstlen(&bset))
	{
		ft_lstfree(&bset);
		return (cset);
	}
	else
	{
		ft_lstfree(&cset);
		return (bset);
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
		return (set);
	}
	path_free(&route);
	return (get_spf_set(edge, vp, len));
}
