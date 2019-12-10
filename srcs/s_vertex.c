
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
	if (i < 0)
		return (NULL);
	while (v && i--)
		v = v->next;
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
	return (0);
}

void				vertex_free(t_vertex **ver)
{
	t_vertex		*p;
	t_vertex		*next;

	p = *ver;
	while (p)
	{
		next = p->next;
		ft_strdel(&p->name);
		free(p);
		p = next;
	}
	p = NULL;
}

void				vertex_print(t_vertex **ver)
{
	t_vertex		*p;

	p = *ver;
	ft_printf("------{red}vertexes{eoc}------\n");
	while (p)
	{
		p->mod == 1 ? ft_printf("{blue}[%s] {eoc}", p->name) :
			p->mod == 2 ? ft_printf("{red}[%s] {eoc}", p->name) :
				ft_printf("[%s] ", p->name);
		ft_printf("X: [%2d], Y: [%2d]\n", p->x, p->y);
		p = p->next;
	}
	ft_printf("--------------------\n");
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

static void				check_existing_vertex(t_vertex **dst, t_vertex *elem, int lc)
{
	t_vertex			*v;

	if (!dst)
		return ;
	v = *dst;
	while (v)
	{
		if (ft_strequ(v->name, elem->name))
			put_error("rooms name already exist", lc);
		v = v->next;
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
	check_existing_vertex((t_vertex **)&structs->ver, elem, inf->lc);
	vertex_push_back((t_vertex **)&structs->ver, elem);
}