#include "lem_in.h"

void				ants_free(t_ants **s)
{
	t_ants			*a;
	t_ants			*next;

	a = *s;
	while (a)
	{
		next = a->next;
		free(a);
		a = next;
	}
	a = NULL;
}


void				edge_free(t_edge **edge)
{
	t_edge			*p;
	t_edge			*next;

	p = *edge;
	while (p)
	{
		next = p->next;
		free(p);
		p = next;
	}
	p = NULL;
}

void				path_free(t_path **s)
{
	t_path			*p;
	t_path			*next;

	p = *s;
	while (p)
	{
		next = p->next_p;
		free(p);
		p = next;
	}
	p = NULL;
}

void			free_list(t_list **tab)
{
	t_list		*lst;
	t_list		*next;
	t_path		*ptr;

	lst = *tab;
	while (lst)
	{
		next = lst->next;
		ptr = lst->content;
		path_free(&ptr);
		free(lst);
		lst = next;
	}
	*tab = NULL;
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