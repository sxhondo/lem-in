/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:41:18 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 12:41:19 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertex			*find_ver_by_index(t_vertex *ver, int i)
{
	while (ver)
	{
		if (ver->i == i)
			return (ver);
		ver = ver->next;
	}
	return (NULL);
}

t_vertex			*find_ver_by_name(t_vertex **ver, char *name)
{
	t_vertex		*v;

	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (NULL);
}

void				add_path_to_lst(t_list **lst, t_path *path)
{
	t_list			*node;

	if (!(node = ft_lstnew(path, sizeof(t_path))))
		put_error("cannot allocate memory", 0);
	free(path);
	ft_lstpushback(lst, node);
}