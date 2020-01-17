/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_route_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:11:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:11:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 					cross_paths(t_path *fn, t_list **ways)
{
	t_list 				*l;
	t_path 				*tmp;

	while (fn)
	{
		l = *ways;
		while (l)
		{
			tmp = l->content;
			while (tmp)
			{
				if (ft_strequ(fn->curr_v->name, tmp->curr_v->name)
						&& fn->curr_v->mod == 0)
					return (1);
				tmp = tmp->next_p;
			}
			l = l->next;
		}
		fn = fn->next_p;
	}
	return (0);
}






//void					put_paths_on_map(t_edge **edge, t_list **ways)
//{
//	t_list 				*w;
//	t_path 				*r;
//	t_edge 				*tmp1;
//	t_edge 				*tmp2;
//
//	w = *ways;
//	wipe_map(edge);
//	while (w)
//	{
//		r = w->content;
////		ft_printf("{red}[ ");
////		path_print(&r, 'f');
////		ft_printf(" ] {eoc}\n");
//		while (r->next_p)
//		{
//			tmp1 = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
//			tmp1->cost += 1;
//			tmp1->del = 0;
//			tmp2 = find_edge(edge, r->next_p->curr_v->name, r->curr_v->name);
//			tmp2->del = 0;
//			if (tmp2->cost >= 1)
//			{
//				tmp1->del = 1;
//				tmp2->del = 1;
//			}
//			r = r->next_p;
//		}
//		w = w->next;
//	}
//}

//void					put_path_on_map(t_edge **edge, t_path *r)
//{
//	t_list 				*w;
//	t_edge 				*tmp1;
//	t_edge 				*tmp2;
//
//	wipe_map(edge);
//	ft_printf("{red}[ ");
//	path_print(&r, 'f');
//	ft_printf(" ] {eoc}\n");
//	while (r->next_p)
//	{
//		tmp1 = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
//		tmp1->cost += 1;
//		tmp1->del = 0;
//		tmp2 = find_edge(edge, r->next_p->curr_v->name, r->curr_v->name);
//		tmp2->del = 0;
//		if (tmp2->cost >= 1)
//		{
//			tmp1->del = 1;
//			tmp2->del = 1;
//		}
//		r = r->next_p;
//	}
//}


//void				delete_route(t_path **route, t_edge **edge)
//{
//	t_path			*r;
//	t_edge			*e;
//
//	r = *route;
//	while (r->next_p)
//	{
//		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
//		e->del = 1;
//		r = r->next_p;
//	}
//}