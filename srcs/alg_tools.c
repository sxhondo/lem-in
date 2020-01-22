/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:45:02 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:45:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path				*get_i_path(t_list *ways, int i)
{
	t_path			*tmp;

	while (ways->next && i--)
		ways = ways->next;
	tmp = ways->content;
	return (tmp);
}

void				turn_edges_off(t_edge *e)
{
	while (e)
	{
		e->on = 0;
		e = e->next;
	}
}

int					*find_sd(t_vertex *ver)
{
	int				*sf;

	if (!(sf = ft_new_array(2, 0)))
		put_error("cannot allocate memory", 0);
	while (ver)
	{
		if (ver->mod == START)
			sf[0] = ver->i;
		if (ver->mod == END)
			sf[1] = ver->i;
		ver = ver->next;
	}
	return (sf);
}

t_path				*trace_route(t_vertex **ver, int *trace, int s, int f)
{
	t_path			*route;
	t_path			*n;
	t_vertex		*v1;

	route = NULL;
	if (trace[f] == -1)
	{
		free(trace);
		return (NULL);
	}
	while (f != s)
	{
		v1 = find_ver_by_index(*ver, f);
		n = path_init(v1);
		path_push(&route, n);
		f = trace[f];
	}
	v1 = find_ver_by_index(*ver, s);
	n = path_init(v1);
	path_push(&route, n);
	free(trace);
	return (route);
}
