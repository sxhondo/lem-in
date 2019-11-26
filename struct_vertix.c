
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
		p->mod == 1 ? ft_printf("{green}[%s] {eoc}", p->name) :
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

void					vertix_push_back(t_vertix **ver, t_vertix *elem)
{
	t_vertix			*tmp;

	tmp = *ver;
	if (!*ver)
		*ver = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
	}
}

void					**get_structures()
{
	t_vertix			*vertix;
	t_edge				*edges;
	void				**tab;

	vertix = NULL;
	edges = NULL;
	tab = (void **)malloc(sizeof(void *) * 3);
	tab[0] = 0;
	tab[1] = vertix;
	tab[2] = edges;
	return (tab);
}
