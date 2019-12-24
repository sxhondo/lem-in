#include "lem_in.h"

void		edge_print(t_edge **edge)
{
	t_edge	*e;

	ft_printf("{blue}------edges----------{eoc}\n");
	e = *edge;
	while (e)
	{
		ft_printf("{blue}%s -> %s{eoc} co: %d bi: %d\n",
				  e->v1->name, e->v2->name, e->cost, e->b);
		e = e->next;
	}
	ft_printf("\n");

}

void				print_all(t_structs *str)
{
	ft_printf("{cyan}ANTS: %14d\n{eoc}", str->ants_amount);
	vertex_print((t_vertex **)&str->ver);
	edge_print((t_edge **)&str->edge);
	ways_print((t_list **)&str->ways);
}

void					print_void_ver(void **ver, int len)
{
	int 	i = 0;
	t_vertex	*v;

	while (i < len)
	{
		v = ver[i];
		ft_printf("[%d] %s ", i, v->name);
		if (v->split == 1)
		{
			ft_printf("i: %d o:%d ", v->in, v->out);
		}
		ft_printf("\n");
		i++;
	}
}

void 			path_print(t_path **path, char mode)
{
	t_path		*tmp;

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
	{
		while (tmp)
		{
			ft_printf("%s ", tmp->curr_v->name);
			tmp = tmp->next_p;
		}
	}
	ft_printf("\n");
}

void				ants_print(t_ants **ants)
{
	t_ants			*an;

	an = *ants;
	while (an)
	{
		ft_printf("{red}id:[%d]{eoc}\t", an->id);
		ft_printf(" {cyan}path: %d{eoc}\t", an->path);
		if (an->pos)
			ft_printf("{green} pos: %s{eoc}\n",  an->pos->curr_v->name);
		else
			ft_printf("{magenta} finished! {eoc}\n");
		an = an->next;
	}
	ft_printf("\n");
}

void 				ways_print(t_list **ways)
{
	int 			i;
	t_list 			*w;

	i = 0;
	w = *ways;
	while (w)
	{
		ft_printf("[%d] ", i++);
		path_print((t_path **)&w->content, 'f');
		w = w->next;
	}
}

void				vertex_print(t_vertex **ver)
{
	int 			i;
	t_vertex		*p;

	i = 0;
	p = *ver;
	ft_printf("{red}------vertexes-------{eoc}\n");
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
}

void		put_error(char *err, int lc)
{
	lc ? ft_fprintf(2, "%d: {red}error: {eoc}", lc) :
		ft_fprintf(2, "{red}error: {eoc}");
	ft_fprintf(2, "%s\n", err);
//	ft_fprintf(2, "ERROR\n");
	exit (1);
}
