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
		tmp += path_len(r) - 1;
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

static t_list 		*handle_small_graph(t_edge **edge, t_vertex **ver)
{
	t_path			*r;
	t_list			*ret;
	int 			s, f;

	ret = NULL;
	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	if (!(r = breadth_first_search(edge, ver, s, f)))
		put_error("no possible solution", 0);
	add_path_to_lst(&ret, r);
	return (ret);
}

static t_path		*suurballe(t_edge *edge, t_vertex *ver)
{
	int 			st;
	int 			fn;
	t_path			*route;

	vertex_print(ver);
	st = find_sf(ver, START);
	fn = find_sf(ver, END);
	if (!(route = breadth_first_search(&edge, &ver, st, fn)))
		return (NULL);
	ft_printf("{red}");
	path_print(&route, 'f');
	ft_printf("\n{eoc}");
	return (route);
}

static void 		put_paths_on_map(t_edge **edge, t_list *set)
{
	t_path			*tmp;
	t_edge			*e;

	e = *edge;
	while (e)
	{
		e->on = 0;
		e = e->next;
	}
	while (set)
	{
		tmp = set->content;
		while (tmp->next_p)
		{
			if ((e = find_edge(edge, tmp->curr_v->name,
					tmp->next_p->curr_v->name)) && e->del == 0)
				e->on = 1;
			tmp = tmp->next_p;
		}
		set = set->next;
	}
}

static void 		turn_off(t_edge **edge, t_path *r)
{
	t_edge			*e;

	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->on = 0;
		r = r->next_p;
	}
}

static t_list 		*collect_turns(t_edge *ce, t_vertex *cv, t_list *set)
{
	int 			s, f;
	t_path			*route;
	t_list 			*bset;

	bset = NULL;
	s = find_sf(cv, START);
	f = find_sf(cv, END);
	put_paths_on_map(&ce, set);
	while ((route = breadth_first_search(&ce, &cv, s, f)))
	{
		turn_off(&ce, route);
		if (!cross_paths(route, &bset))
			add_path_to_lst(&bset, route);
		else
			path_free(&route);
	}
	ways_print(&bset);
	return (bset);
}

int 				compare_sets(t_structs *s)
{
	int 			cf_a;
	int 			cf_b;

	if (s->a_set == NULL || s->b_set == NULL)
		return (1);
	cf_a = get_cf(s->a_set, s->ants_amount);
	cf_b = get_cf(s->b_set, s->ants_amount);
	ft_printf("%d - %d\n", cf_a, cf_b);
	if (cf_b > cf_a)
	{
		free_list(&s->b_set);
		return (1);
	}
	free_list(&s->a_set);
	return (1);
}

t_list				*solver(t_structs *s)
{
	t_path			*route;

	s->x_set = handle_small_graph(&s->ce, &s->cv);
	if (path_len((t_path *)s->x_set->content) == 2)
		return (s->x_set);
	flip_divide((t_path **)&s->x_set->content, &s->ce, &s->cv);
	re_route_edges(&s->ce, s->cv);
	while (compare_sets(s))
	{
		s->a_set = s->b_set;
		if (!(route = suurballe(s->ce, s->cv)))
			break ;
		flip_divide(&route, &s->ce, &s->cv);
		vertex_print(s->cv);
		edge_print(s->ce);
		re_route_edges(&s->ce, s->cv);
		delete_inverse_edges(s->ce, s->edge, route);
		add_path_to_lst(&s->x_set, route);
		s->b_set = collect_turns(s->edge, s->ver, s->x_set);
	}
	return (s->a_set ? s->a_set : s->b_set);
}