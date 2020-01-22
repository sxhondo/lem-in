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

t_path			*get_i_path(t_list *ways, int i)
{
	t_path		*tmp;

	while (ways->next && i--)
		ways = ways->next;
	tmp = ways->content;
	return (tmp);
}

int 			*find_sd(t_vertex *ver)
{
	int 		*sf;

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