
#include "lem_in.h"

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
	{
		put_error(12, 0);
		return (0);
	}
	ver->mod = mod;
	if (!(ver->name = ft_strdup(name)))
		put_error(12, 0);
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
				put_error(15, lc);
			tmp = tmp->next;
		}
		if ((ft_strequ(tmp->name, elem->name)))
			put_error(15, lc);
		tmp->next = elem;
		elem->next = NULL;
	}
}

int						lst_len(void **lst, unsigned mod)
{
	int 				i;
	t_vertix			*v;
	t_edge				*e;

	i = 0;
	if (mod == 0)
	{
		v = *lst;
		while (v && ++i)
			v = v->next;
	}
	else if (mod == 1)
	{
		e = *lst;
		while (e && ++i)
			e = e->next;
	}
	return (i);
}