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

void				swap_ver(t_vertex **v1, t_vertex **v2)
{
	t_vertex		*tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

//t_path				*trace_route(void **ver, int *trace, int last)
//{
//	t_path			*route;
//	t_path			*n;
//	t_vertex		*v1;
//
//	route = NULL;
//	if (trace[last] == -1)
//	{
//		free(trace);
//		return (NULL);
//	}
//	while (last > 0)
//	{
//		v1 = (t_vertex *)ver[last];
//		n = path_init(v1);
//		path_push(&route, n);
//		last = trace[last];
//	}
//	v1 = (t_vertex *)ver[0];
//	n = path_init(v1);
//	path_push(&route, n);
//	free(trace);
//	return (route);
//}

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

t_path				*trace_route(t_vertex **ver, int *trace, int last)
{
	t_path			*route;
	t_path			*n;
	t_vertex		*v1;

	route = NULL;
	if (trace[last] == -1)
	{
		free(trace);
		return (NULL);
	}
	while (last > 0)
	{
		v1 = find_ver_by_index(*ver, last);
//		v1 = (t_vertex *)ver[last];
		n = path_init(v1);
		path_push(&route, n);
		last = trace[last];
	}
	v1 = (t_vertex *)ver[0];
	n = path_init(v1);
	path_push(&route, n);
	free(trace);
	return (route);
}