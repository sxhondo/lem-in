#include "lem_in.h"

void		edge_print(t_edge **edge)
{
	t_edge	*e;

	ft_printf("---edges---\n");
	e = *edge;
	while (e)
	{
		ft_printf("{blue}%s - %s{eoc} %d\n",
				  e->v1->name, e->v2->name, e->cost);
		e = e->next;
	}
}

void		free_path(t_path **s)
{
	t_path	*p;
	t_path	*next;

	p = *s;
	while (p)
	{
		next = p->next_p;
		free(p);
		p = next;
	}
}

void				print_all(t_structs *str)
{
	ft_printf("{cyan}ANTS: %14d\n{eoc}", str->ants_amount);
	vertex_print((t_vertex **)&str->ver);
	edge_print((t_edge **)&str->edge);
//	print_mx(str->mx, str->m_size, (t_vertex **)&str->ver);
	paths_print(&str->paths, (t_vertex **)&str->ver);
//	ants_print((t_ants **)&str->ants, (t_vertex **)&str->ver);
}

void			paths_print(t_list **lst, t_vertex **ver)
{
	t_list		*p;
	t_path		*ptr;
	int 		i;

	// i = 0;
	// p = *lst;
	// while (p)
	// {
	// 	ft_printf("Path [%d]: ", i++);
	// 	ptr = p->content;
	// 	path_print(&ptr, ver);
	// 	p = p->next;
	// }
	// ft_printf("\n");
}

/* f == from front, b = from back */

void 			path_print(t_path **path, char mode)
{
	t_path		*tmp;

 	ft_printf("from %s\n", mode == 'f' ? "back" : "front");
	tmp = *path;
	if (mode == 'b')
	{
		while (tmp->next_p)
			tmp = tmp->next_p;
		while (tmp)
		{
			ft_printf("%s ", tmp->curr_v->name);
			tmp = tmp->prev_p;
		}
	}
	else
		while (tmp)
		{
			ft_printf("%s ", tmp->curr_v->name);
			tmp = tmp->next_p;
		}
	ft_printf("\n");
}

void				vertex_print(t_vertex **ver)
{
	int 			i;
	t_vertex		*p;

	i = 0;
	p = *ver;
	ft_printf("------{red}vertexes{eoc}-------\n");
	while (p)
	{
		ft_printf("[%d] ", i++);
		p->mod == 1 ? ft_printf("{blue}%s {eoc}", p->name) :
			p->mod == 2 ? ft_printf("{red}%s {eoc}", p->name) :
				ft_printf("%s ", p->name);
		ft_printf("\n");
		// ft_printf("X: [%2d], Y: [%2d]\n", p->x, p->y);
		p = p->next;
	}
	ft_printf("---------------------\n");
}

void		put_error(char *err, int lc)
{
	lc ? ft_printf("%d: {red}error: {eoc}", lc) :
		ft_printf("{red}error: {eoc}");
	ft_printf("%s\n", err);
//	ft_printf("ERROR\n");
	exit (1);
}
