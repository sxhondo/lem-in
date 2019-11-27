#include "lem_in.h"

void				edge_free(t_edge **edge)
{
	t_edge			*p;
	t_edge			*next;

	p = *edge;
	while (p)
	{
		next = p->next;
		ft_strdel(&p->e1);
		ft_strdel(&p->e2);
		free(p);
		p = next;
	}
	p = NULL;
}

void				edge_print(t_edge **edge)
{
	t_edge			*p;

	p = *edge;
	ft_printf("------{blue}LINKS{eoc}---------\n");
	while (p)
	{
		ft_printf("{red} %s-{blue}%s{eoc}\n", p->e1, p->e2);
		p = p->next;
	}
	ft_printf("--------------------\n");
}

void				edge_push_back(t_edge **edge, t_edge *elem, t_vertix **ver, int lc)
{
	int 			i;
	int 			j;
	t_edge			*tmp;
	t_vertix		*v;

	j = 0;
	i = 0;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, elem->e1))
			i++;
		if (ft_strequ(v->name, elem->e2))
			j++;
		v = v->next;
	}
	if (i == 0 || j == 0)
		put_error(16, lc);
	tmp = *edge;
	if (!*edge)
		*edge = elem;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
		elem->next = NULL;
	}
}

t_edge				*edge_init(char *e1, char *e2)
{
	t_edge			*edge;

	if (!(edge = ft_memalloc(sizeof(t_edge))))
	{
		put_error(12, 0);
		return (0);
	}
	edge->e1 = e1;
	edge->e2 = e2;
	return (edge);
}
