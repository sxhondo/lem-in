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

int 			find_sf(t_vertex *ver, int sf)
{

	while (ver)
	{
		if (ver->mod == sf)
			return (ver->i);
		ver = ver->next;
	}
	return (-1);
}

t_vertex					*find_ver_by_name(t_vertex **ver, char *name)
{
	t_vertex				*v;

	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (NULL);
}

t_vertex				*find_ver_by_index(t_vertex *ver, int i)
{
	while (ver)
	{
		if (ver->i == i)
			return (ver);
		ver = ver->next;
	}
	return (NULL);
}

t_path				*trace_route(t_vertex **ver, int *trace)
{
	t_path			*route;
	t_path			*n;
	t_vertex		*v1;
	int 			s, f;

	s = find_sf(*ver, START);
	f = find_sf(*ver, END);
	route = NULL;
	if (trace[f] == -1)
	{
		free(trace);
		return (NULL);
	}
	while (f > 0)
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