#include "lem_in.h"

void		edge_print(t_edge **edge)
{
	t_edge	*e;

	ft_printf("\t---edges---\n");
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
		next = p->next;
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

	i = 0;
	p = *lst;
	while (p)
	{
		ft_printf("Path [%d]: ", i++);
		ptr = p->content;
		path_print(&ptr, ver);
		p = p->next;
	}
	ft_printf("\n");
}

void			path_print(t_path **path, t_vertex **ver)
{
	int 		i;
	t_path		*ptr;

//	i = 1;
//	ptr = *path;
//	while (ptr)
//	{
////		ft_printf("(%d)", ptr->node);
//		if (i == 1)
//			ft_printf("{red}%s->{eoc}",
//					  find_ver_by_index(ver, ptr->node)->name);
//		else if (i != path_len(path))
//			ft_printf("{green}%s->{eoc}",
//					  find_ver_by_index(ver, ptr->node)->name);
//		else if (i == path_len(path))
//			ft_printf("{blue}%s{eoc}",
//					  find_ver_by_index(ver, ptr->node)->name);
//		i++;
//		ptr = ptr->next;
//	}
//	ft_printf("\n");
}

//void				ants_print(t_ants **ants, t_vertex **ver)
//{
//	t_ants			*an;
//
//	an = *ants;
//	while (an)
//	{
//		ft_printf("{red}id:[%d]{eoc}\t", an->id);
//		ft_printf(" {cyan}path: %d{eoc}\t", an->path);
//		if (an->pos)
//		{
//			ft_printf("{green} pos: %d{eoc}",  an->pos->node);
//			ft_printf("{green} (%s){eoc}\n",
//					  find_ver_by_index(ver, an->pos->node)->name);
//		}
//		else
//			ft_printf("{magenta} finished! {eoc}\n");
//		an = an->next;
//	}
//	ft_printf("\n");
//}

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
		p->mod == 1 ? ft_printf("{blue}[%s] {eoc}", p->name) :
			p->mod == 2 ? ft_printf("{red}[%s] {eoc}", p->name) :
				ft_printf("[%s] ", p->name);
		ft_printf("X: [%2d], Y: [%2d]\n", p->x, p->y);
		p = p->next;
	}
	ft_printf("---------------------\n");
}

//void				edge_print(t_edge **edge)
//{
//	t_edge			*p;
//
//	p = *edge;
//	ft_printf("------{blue}edges{eoc}----------\n");
//	while (p)
//	{
//		ft_printf("{red} %s-{blue}%s{eoc}\n", p->v1, p->v2);
//		p = p->next;
//	}
//	ft_printf("---------------------\n");
//}

void			print_mx(int **mx, int size, t_vertex **ver)
{
	int 		i, j;
	t_vertex 	*p;

	p = NULL;
	ft_printf("------{magenta}matrix{eoc}---------\n   ");
	p = *ver;
	while (p)
	{
		p->mod == 0 ? ft_printf("%3s", p->name) :
			p->mod == 1 ? ft_printf("{red}%3s{eoc}", p->name) :
				ft_printf("{blue}%3s{eoc}", p->name);
		p = p->next;
	}
	p = *ver;
	ft_printf("\n");
	i = -1;
	while (++i < size)
	{
		p->mod == 0 ? ft_printf("%3s", p->name) :
			p->mod == 1 ? ft_printf("{red}%3s{eoc}", p->name) :
				ft_printf("{blue}%3s{eoc}", p->name);
		p = p->next;
		j = -1;
		while (++j < size)
			mx[i][j] == 0 ? ft_printf("%3d", mx[i][j])
			: ft_printf("{red}%3d{eoc}", mx[i][j]);
		ft_printf("\n");
	}
	ft_printf("---------------------\n\n");
}

void		put_error(char *err, int lc)
{
	lc ? ft_printf("%d: {red}error: {eoc}", lc) :
		ft_printf("{red}error: {eoc}");
	ft_printf("%s\n", err);
//	ft_printf("ERROR\n");
	exit (1);
}
