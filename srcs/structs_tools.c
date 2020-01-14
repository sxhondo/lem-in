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

void				vertex_new(t_vertex **ver, char *name, unsigned div)
{
	t_vertex		*elem;
	char 			*str;
	unsigned 		d;

	d = 0;
	if (!(elem = ft_memalloc(sizeof(t_vertex))))
	{
		put_error("cannot allocate memory", 0);
		return ;
	}
	str = ft_strdup(name);
	elem->name = str;
	elem->div |= div;
	elem->mod = 0;
	elem->vis = 0;
	vertex_insert(ver, elem);
}

int					get_index_of_ver(void **v, char *name, int size)
{
	t_vertex		*tmp;
	int				i;

	i = 0;
	while (i < size)
	{
		tmp = (t_vertex *)v[i];
		if (ft_strequ(tmp->name, name) && (tmp->div == 0 || tmp->div == 1))
			return (i);
		i++;
	}
	return (-1);
}

void				add_path_to_lst(t_list **lst, t_path *path)
{
	t_list			*node;

	if (!(node = ft_lstnew(path, sizeof(t_path))))
		put_error("cannot allocate memory", 0);
	free(path);
	ft_lstpushback(lst, node);
}

void				**convert_ver_to_ptrs(t_vertex **ver, int len)
{
	t_vertex		*v;
	void			**ptr;
	int				i;

	i = 0;
	ptr = ft_new_ptr_array(len);
	v = *ver;
	while (v)
	{
		ptr[i] = v;
		i++;
		v = v->next;
	}
	return (ptr);
}
