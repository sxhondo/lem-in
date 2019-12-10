#include "lem_in.h"

void				edge_free(t_edge **edge)
{
	t_edge			*p;
	t_edge			*next;

	p = *edge;
	while (p)
	{
		next = p->next;
		ft_strdel(&p->v1);
		ft_strdel(&p->v2);
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
		ft_printf("{red} %s-{blue}%s{eoc}\n", p->v1, p->v2);
		p = p->next;
	}
	ft_printf("--------------------\n");
}

static t_edge				*edge_init(char *e1, char *e2)
{
	t_edge					*edge;

	if (!(edge = ft_memalloc(sizeof(t_edge))))
	{
		put_error("cannot alocate memory", 0);
		return (NULL);
	}
	if (!(edge->v1 = ft_strdup(e1)))
		put_error("cannot alocate memory", 0);
	if (!(edge->v2 = ft_strdup(e2)))
		put_error("cannot alocate memory", 0);
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

static void				check_non_existing_link(t_vertex **ver, int lc,
									char *v1, char *v2)
{
	int 				i;
	int 				j;
	t_vertex			*v;

	i = 0;
	j = 0;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, v1))
			i++;
		if (ft_strequ(v->name, v2))
			j++;
		v = v->next;
	}
	if (i == 0 || j == 0)
		put_error("room name doesnt exist", lc);
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

void 						edge_add(t_structs *structs, t_info *inf)
{
	t_edge					*elem;

	elem = proceed_edge(inf);
	check_non_existing_link((t_vertex **)&structs->ver,
			inf->lc, elem->v1, elem->v2);
	edge_push_back((t_edge **)&structs->edge, elem);
}
