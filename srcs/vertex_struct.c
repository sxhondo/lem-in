
#include "lem_in.h"

int 					vertex_len(t_vertex **ver)
{
	int 				i;
	t_vertex			*v;

	i = 0;
	v = *ver;
	while (v)
	{
		i++;
		v = v->next;
	}
	return (i);
}

t_vertex 			*find_ver_by_index(t_vertex **ver, int i)
{
	t_vertex 		*v;

	v = *ver;
	while (v && i--)
	{
		ft_printf("%d\n", i);
		v = v->next;
	}
	return (v);
}

int							get_i_by_name(t_vertex **ver, char *name)
{
	t_vertex				*v;
	int 					i;

	i = 0;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (i);
		v = v->next;
		i++;
	}
	return (-1);
}


t_vertex     			 *find_ver_by_name(t_vertex **ver, char *name)
{
	t_vertex   			 *v;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (NULL);
}

static void					vertex_push_back(t_vertex **dst, t_vertex *elem)
{
	t_vertex				*tmp;

	tmp = *dst;
	if (!*dst)
		*dst = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
	}
}

void 					vertex_add(t_structs *structs,
												t_info *inf, int x, int y)
{
	t_vertex			*elem;

	if (!(elem = ft_memalloc(sizeof(t_vertex))))
	{
		put_error("cannot allocate memory", 0);
		return ;
	}
	if (!(elem->name = ft_strdup(inf->name)))
	{
		put_error("cannot allocate memory", 0);
		return ;
	}
	elem->mod = inf->mod;
	elem->x = x;
	elem->y = y;
	elem->split = 0;
	elem->in = 0;
	elem->out = 0;
	vertex_push_back((t_vertex **)&structs->ver, elem);
}
