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

t_list				*duplicate_set(t_list *s)
{
	t_list 			*lst = NULL;
	t_list			*node;

	while (s)
	{
		if (!(node = ft_lstnew(s->content, sizeof(t_path))))
			put_error("cannot allocate memory", 0);
		ft_lstpushback(&lst, node);
		s = s->next;
	}
	return (lst);
}

void				add_path_to_lst(t_list **lst, t_path *path)
{
	t_list			*node;

	if (!(node = ft_lstnew(path, sizeof(t_path))))
		put_error("cannot allocate memory", 0);
	free(path);
	ft_lstpushback(lst, node);
}

int					get_index_of_ver(void **vp, t_vertex *v, int size)
{
	t_vertex		*tmp;
	int				i;

	i = 0;
	while (i < size)
	{
		tmp = (t_vertex *)vp[i];
		if (ft_strequ(tmp->name, v->name) && v->div == tmp->div)
			return (i);
		i++;
	}
	return (-1);
}

void				set_indexes_of_ver(t_edge **edge, void **ver, int len)
{
	t_edge			*e;
	t_vertex		*tmp;
	int 			i;

	i = 0;
	e = *edge;
	while (e)
	{
		e->v1->i = get_index_of_ver(ver, e->v1, len);
		e->v2->i = get_index_of_ver(ver, e->v2, len);
		e = e->next;
	}
}

void 				update_indexes(t_vertex *ver)
{
	int 			i;

	i = 0;
	while (ver)
	{
		ver->i = i++;
		ver = ver->next;
	}
}


void				**convert_ver_to_ptrs(t_vertex **ver, t_edge **edge, int len)
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
	set_indexes_of_ver(edge, ptr, len);
	return (ptr);
}
