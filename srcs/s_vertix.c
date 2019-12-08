
#include "incs/lem_in.h"

int 					ver_len(t_vertix **ver)
{
	int 				i;
	t_vertix			*v;

	i = 0;
	v = *ver;
	while (v)
	{
		i++;
		v = v->next;
	}
	return (i);
}

t_vertix 			*find_ver_by_index(t_vertix **ver, int i)
{
	t_vertix 		*v;

	v = *ver;
	if (i < 0)
		return (NULL);
	while (v && i--)
		v = v->next;
	return (v);
}

//char 					*find_ver_by_index(t_vertix **ver, int i)
//{
//	t_vertix 		*v;
//	int 				j;
//
//	j = 0;
//	v = *ver;
//	while (v)
//	{
//		if (j == i)
//			return (v->name);
//		j++;
//		v = v->next;
//	}
//}

t_vertix     			 *find_ver_by_name(t_vertix **ver, char *name)
{
	t_vertix   			 *v;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (0);
}

void				vertix_free(t_vertix **ver)
{
	t_vertix		*p;
	t_vertix		*next;

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

void				vertix_print(t_vertix **ver)
{
	t_vertix		*p;

	p = *ver;
	ft_printf("------{red}VERTIXES{eoc}------\n");
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

t_vertix			*vertix_init(unsigned mod, char *name, const int *xy)
{
	t_vertix		*ver;

	if (!(ver = ft_memalloc(sizeof(t_vertix))))
		return (put_error(12, 0, NULL));
	ver->mod = mod;
	if (!(ver->name = ft_strdup(name)))
		put_error(12, 0, NULL);
	ver->x = xy[0];
	ver->y = xy[1];
	ver->next = NULL;
	return (ver);
}

void					vertix_push_back(t_vertix **ver, t_vertix *elem, int lc)
{
	t_vertix			*tmp;

	tmp = *ver;
	if (!*ver)
		*ver = elem;
	else
	{
		while (tmp->next)
		{
			if ((ft_strequ(tmp->name, elem->name)))
				put_error(15, lc, NULL);
			tmp = tmp->next;
		}
		if ((ft_strequ(tmp->name, elem->name)))
			put_error(15, lc, NULL);
		tmp->next = elem;
		elem->next = NULL;
	}
}