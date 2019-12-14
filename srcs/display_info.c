#include "lem_in.h"

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

void				ants_print(t_ants **ants, t_vertex **ver)
{
	t_ants			*an;

	an = *ants;
	while (an)
	{
		ft_printf("{red}id:[%d]\t", an->id);
		ft_printf(" {cyan}path: %d\t", an->path);
		if (an->pos)
		{
			ft_printf("{green} pos: %d",  an->pos->node);
			ft_printf("{green} (%s)\n",
					  find_ver_by_index(ver, an->pos->node)->name);
		}
		else
			ft_printf("{magenta} finished! {eoc}\n");
		an = an->next;
	}
	ft_printf("\n");
}

void				vertex_print(t_vertex **ver)
{
	t_vertex		*p;

	p = *ver;
	ft_printf("------{red}vertexes{eoc}------\n");
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

void			print_mx(int **mx, int size, t_vertex **ver)
{
	int 		i, j;
	t_vertex 	*p;

	p = NULL;
	ft_printf("\n   ");
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
	ft_printf("\n");
}

void		put_error(char *err, int lc)
{
	lc ? ft_printf("%d: {red}error: {eoc}", lc) :
		ft_printf("{red}error: {eoc}");
	ft_printf("%s\n", err);
	exit (1);
}
