#include "lem_in.h"

void				edge_free(t_edge **edge)
{
	t_edge			*p;
	t_edge			*next;

	p = *edge;
	while (p)
	{
		next = p->next;
		ft_strdel(&p->v1_name);
		ft_strdel(&p->v2_name);
		free(p);
		p = next;
	}
	p = NULL;
}

static t_edge				*edge_init(char *e1, char *e2)
{
	t_edge					*edge;

	if (!(edge = ft_memalloc(sizeof(t_edge))))
	{
		put_error("cannot alocate memory", 0);
		return (NULL);
	}
	if (!(edge->v1_name = ft_strdup(e1)))
		put_error("cannot alocate memory", 0);
	if (!(edge->v2_name = ft_strdup(e2)))
		put_error("cannot alocate memory", 0);
	edge->cost = 1;
	ft_strdel(&e1);
	ft_strdel(&e2);
	return (edge);
}

static t_edge 				*proceed_edge(t_info *inf)
{
	int 					i;
	char 					*v1;
	char 					*v2;
	char 					*name;

	name = inf->name;
	if (inf->mod)
		put_error("link cannot be room-modificator", inf->lc);
	i = cut_after_symbol(name, &v1, '-');
	name += i;
	if (!*name || !(*name + 1))
		put_error("link not well formatted", inf->lc);
	name += 1;
	if (!(v2 = ft_strdup(name)))
		put_error("cannot alocate memory", 0);
	return (edge_init(v1, v2));
}

static void					edge_push_back(t_edge **dst, t_edge *elem)
{
	t_edge					*tmp;

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

t_edge						*find_edge(t_edge **edge, char *v1, char *v2)
{
	t_edge					*e;

	e = *edge;
	while (e)
	{
		if ((ft_strequ(e->v1->name, v1) && ft_strequ(e->v2->name, v2)) ||
				(ft_strequ(e->v1->name, v2) && ft_strequ(e->v2->name, v1)))
			return (e);
		e = e->next;
	}
	return (NULL);
}

t_vertex					*find_start(t_edge **edge)
{
	t_edge					*e;

	e = *edge;
	while (e)
	{
		if (e->v1->mod == 1)
			return (e->v1);
		if (e->v2->mod == 1)
			return (e->v2);
		e = e->next;
	}
	return (NULL);
}

int 						edge_len(t_edge **edge)
{
	t_edge					*e;
	int 					i;

	i = 0;
	e = *edge;
	while (e)
	{
		e = e->next;
		i++;
	}
	return (i);
}

void 						edge_add(t_structs *structs, t_info *inf)
{
	t_edge					*elem;

	elem = proceed_edge(inf);
	edge_push_back((t_edge **)&structs->edge, elem);
}
