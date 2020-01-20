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

	if (len != 0)
	{
		if (tmp % len)
			tmp--;
		tmp = tmp / len;
	}
	return (tmp);
}

static t_edge 		*copy_edge(t_edge *edge)
{
	t_edge			*d = NULL;
	t_edge			*n;

	while (edge)
	{
		if (!(n = ft_memalloc(sizeof(t_edge))))
			put_error("cannot allocate memory", 0);
		else
		{
			n->v1 = edge->v1;
			n->v2 = edge->v2;
			n->del = 0;
			n->on = 1;
			edge_push_back(&d, n);
			edge = edge->next;
		}
	}
	return (d);
}

static t_vertex		*copy_ver(t_vertex *ver)
{
	t_vertex		*d = NULL;
	t_vertex		*v;

	while (ver)
	{
		v = ft_memalloc(sizeof(t_vertex));
		v->name = ver->name;
		v->i = ver->i;
		v->mod = ver->mod;
		vertex_push_back(&d, v);
		ver = ver->next;
	}
	return (d);
}

static void 		turn_path_off(t_path *p, t_edge *edge)
{
	t_edge			*tmp;

	while (p->next_p)
	{
		tmp = find_edge(&edge, p->curr_v->name, p->next_p->curr_v->name);
		tmp->on = 0;
		tmp->v1->mark = 1;
		p = p->next_p;
	}
}

static void 		reset_map(t_edge *e)
{
	while (e)
	{
		e->on = 1;
		e->v1->mark = 0;
		e->v2->mark = 0;
		e = e->next;
	}
}

static void 		delete_inverse_edges(t_edge *a, t_edge *b, t_path *r)
{
	t_edge			*tmp;

	while (r->next_p)
	{
		tmp = find_edge(&b, r->curr_v->name, r->next_p->curr_v->name);
		tmp->del = 0;
		r = r->next_p;
	}
	while (a)
	{
		if (a->del == 1)
		{
			tmp = find_edge(&b, a->v1->name, a->v2->name);
			tmp->del = 1;
		}
		a = a->next;
	}
}

static t_list 		*get_new_set(t_edge *edge, t_vertex *ver)
{
	t_path			*r;
	t_list 			*set = NULL;
	int 			s, f;

	s = find_sf(ver, START);
	f = find_sf(ver, END);
	while ((r = breadth_first_search(&edge, &ver, s, f)))
	{
		turn_path_off(r, edge);
		add_path_to_lst(&set, r);
	}
	reset_map(edge);
	return (set);
}

static int			suurballe(t_edge *edge, t_vertex *ver, t_edge *e, int ml)
{
	int 			st;
	int 			fn;
	t_path			*route;

	st = find_sf(ver, START);
	fn = find_sf(ver, END);
	if (!(route = breadth_first_search(&edge, &ver, st, fn)))
		return (0);

	ft_printf("{red}");
	path_print(&route, 'f');
	ft_printf("\n{eoc}");

	flip_divide(&route, &edge, &ver);
	delete_inverse_edges(edge, e, route);
	return (1);
}

static int 			compare(t_list *set, t_list *p_set, int ants)
{
	int 			cf1;
	int 			cf2;

	if (set == NULL || p_set == NULL)
		return (1);
//	ft_printf("{green}%d - %d{eoc}\n", get_cf(set, ants), get_cf(p_set, ants));
	cf1 = get_cf(set, ants);
	cf2 = get_cf(p_set, ants);
}

t_list				*solver(int ants, t_edge **edge, t_vertex **ver)
{
	t_edge			*e;
	t_vertex		*v;
	t_list 			*set = NULL;
	t_list 			*p_set = NULL;
	int 			ml = 0;

	e = copy_edge(*edge);
	v = copy_ver(*ver);
	while ((suurballe(*edge, *ver, e, ml++)))
	{
		set = get_new_set(e, v);
		ways_print(&set);

//		if (!(set = get_new_set(e, v))
//			|| !(compare(set, p_set, ants)))
//			break ;
//		p_set = set;
	}
	return (set);
}

//	while ((route = breadth_first_search(edge, ver, sf[0], sf[1])))
//	{
//		flip_divide(&route, edge, ver);
//		re_route_edges(edge, *ver);
//		delete_inverse_edges(*edge, e, route);
//		if (!(set = get_new_set(e, v , ++ml)))
//			break ;
//		ways_print(&set);
//		ft_printf("{green}%d - %d{eoc}\n", get_cf(set, ants), (p_set == NULL) ?
//												  NULL : get_cf(p_set, ants));
//		if (get_cf(set, ants) > cf)
//		{
//			free_list(&set);
//			break ;
//		}
//		else
//		{
//			cf = get_cf(set, ants);
//			free_list(&p_set);
//			p_set = set;
//		}
//	}
//	return (p_set);
//}