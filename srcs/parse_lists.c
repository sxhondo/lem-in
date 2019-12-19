#include "lem_in.h"

static t_vertex			*iter_to_last(t_vertex **ver)
{
	t_vertex			*ptr;

	ptr = *ver;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void				small_swap(t_vertex **ver)
{
	t_vertex			*v;
	t_vertex			*next;

	v = *ver;
	next = v->next;
	v->next = NULL;
	next->next = v;
	*ver = next;
}

static void				first_swap(t_vertex **ver)
{
	t_vertex			*v;
	t_vertex			*last;
	t_vertex			*next;

	last = iter_to_last(ver);
	v = *ver;
	next = v->next;
	v->next = NULL;
	last->next = v;
	*ver = next;
}

static void				swap_lst(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*last;
	t_vertex			*prev;
	t_vertex			*next;

	p = *ver;
	while (p)
	{
		if (p->next->mod == 2)
		{
			prev = p;
			next = p->next->next;
			last = iter_to_last(ver);
			last->next = p->next;
			p->next->next = NULL;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}

static void				put_to_end(t_vertex **ver)
{
	t_vertex			*v;
	t_vertex			*last;

	last = iter_to_last(ver);
	if (last->mod == 2)
		return ;
	if (vertex_len(ver) == 2)
		return (small_swap(ver));
	v = *ver;
	if (v->mod == 2)
		return (first_swap(ver));
	else
		swap_lst(ver);
}

static void				put_to_begin(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*prev;
	t_vertex			*next;

	if ((*ver)->mod == 1)
		return ;
	p = *ver;
	while (p)
	{
		if (p->next->mod == 1)
		{
			prev = p;
			next = p->next->next;
			p->next->next = *ver;
			(*ver) = p->next;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}

static void				check_duplicate_vertex(t_vertex **ver)
{
	t_vertex			*i;
	t_vertex			*j;
	int 				err;

	i = *ver;
	while (i)
	{
		err = 0;
		j = *ver;
		while (j)
		{
			if (ft_strequ(j->name, i->name))
				err++;
			j = j->next;
		}
		if (err > 1)
			put_error("duplicated room names", 0);
		i = i->next;
	}
}

static void				check_non_existing_vertex(t_vertex **ver, t_edge **edge)
{
	t_vertex			*v;
	t_edge				*e;
	int 				i;
	int 		j;

	e = *edge;
	while (e)
	{
		i = 0;
		j = 0;
		v = *ver;
		while (v)
		{
			if (ft_strequ(e->v1_name, v->name))
				i++;
			if (ft_strequ(e->v2_name, v->name))
				j++;
			v = v->next;
		}
		if (i == 0 || j == 0)
			put_error("room name does not exist", 0);
		e = e->next;
	}
}

static void		link_edges_to_vertex(t_vertex **ver, t_edge **edge)
{
	t_edge		*e;

	e = *edge;
	while (e)
	{
		e->v1 = find_ver_by_name(ver, e->v1_name);
		e->v2 = find_ver_by_name(ver, e->v2_name);
		ft_strdel(&e->v1_name);
		ft_strdel(&e->v2_name);
		e = e->next;
	}
}

void 			parse_lists(t_vertex **ver, t_edge **edge)
{
	if (!*edge)
		put_error("no links given", 0);
	check_duplicate_vertex(ver);
	check_non_existing_vertex(ver, edge);
	link_edges_to_vertex(ver, edge);
	put_to_end(ver);
	put_to_begin(ver);
}
