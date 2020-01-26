// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   alg_solver.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/12/26 12:35:57 by sxhondo           #+#    #+#             */
// /*   Updated: 2019/12/26 12:35:58 by sxhondo          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "lem_in.h"

// static t_list		*handle_small_graph(t_edge **edge, t_vertex **ver, int *sf)
// {
// 	t_path			*r;
// 	t_list			*ret;

// 	ret = NULL;
// 	if (!(r = breadth_first_search(edge, ver, sf[0], sf[1])))
// 		put_error("no possible solution", 0);
// 	if (path_len(r) == 2)
// 		free(sf);
// 	add_path_to_lst(&ret, r);
// 	return (ret);
// }

// static t_list		*correct_free(t_structs *s, int *sf)
// {
// 	t_list			*tmp;

// 	free_list(&s->x_set);
// 	if (s->a_set == NULL && s->b_set == NULL)
// 	{
// 		tmp = handle_small_graph(&s->edge, &s->ver, sf);
// 		free(sf);
// 		return (tmp);
// 	}
// 	free(sf);
// 	if (s->a_set != NULL && s->a_set == s->b_set)
// 		return (s->a_set);
// 	if (s->a_set)
// 	{
// 		free_list(&s->b_set);
// 		return (s->a_set);
// 	}
// 	if (s->b_set)
// 	{
// 		free_list(&s->a_set);
// 		return (s->b_set);
// 	}
// 	return (NULL);
// }

// int					compare_sets(t_structs *s)
// {
// 	int				cf_a;
// 	int				cf_b;

// 	if (s->a_set == NULL || s->b_set == NULL)
// 		return (1);
// 	cf_a = calculate_actions(s->a_set, s->ants_amount);
// 	cf_b = calculate_actions(s->b_set, s->ants_amount);
// 	if (cf_b > cf_a)
// 	{
// 		free_list(&s->b_set);
// 		return (0);
// 	}
// 	free_list(&s->a_set);
// 	return (1);
// }

// static t_path		*suurballe(t_edge *edge, t_vertex *ver, int *sf)
// {
// 	t_path			*route;

// 	if (!(route = breadth_first_search(&edge, &ver, sf[0], sf[1])))
// 		return (NULL);
// 	return (route);
// }

// t_list				*solver(t_structs *s)
// {
// 	t_path			*route;
// 	int				*sf;

// 	sf = find_sd(s->ver);
// 	s->x_set = handle_small_graph(&s->ce, &s->cv, sf);
// 	if (path_len((t_path *)s->x_set->content) == 2 || s->ants_amount == 1)
// 		return (s->x_set);
// 	flip_divide((t_path **)&s->x_set->content, &s->ce, &s->cv);
// 	re_route_edges(&s->ce, s->cv);
// 	while (compare_sets(s))
// 	{
// 		s->a_set = s->b_set;
// 		if (!(route = suurballe(s->ce, s->cv, sf)))
// 			break ;
// 		flip_divide(&route, &s->ce, &s->cv);
// 		re_route_edges(&s->ce, s->cv);
// 		add_path_to_lst(&s->x_set, route);
// 		s->b_set = collect_turns(s->edge, s->ver, s->x_set, sf);
// 	}
// 	return (correct_free(s, sf));
// }
