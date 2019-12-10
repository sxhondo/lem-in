#include "lem_in.h"

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

int			exclude_overlap(int **mx, int size)
{
	int 	i;
	int 	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (mx[i][j] == 1 && mx[j][i] == 1)
			{
				mx[i][j] = 0;
				mx[j][i] = 0;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void		set_to_zero(int **mx, int size)
{
	int 	i;
	int 	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mx[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void				fill_mx(int **mx, t_edge **edge, t_vertex **ver)
{
	t_edge 				*e;

	e = *edge;
	while (e)
	{
		mx[get_i_by_name(ver, e->v1)][get_i_by_name(ver, e->v2)] = 1;
		mx[get_i_by_name(ver, e->v2)][get_i_by_name(ver, e->v1)] = 1;
		e = e->next;
	}
}

void 					create_matrix(t_structs *structs)
{
	int 				**m;
	int 				size;

	size = vertex_len((t_vertex **)&structs->ver);
	m = ft_allocate_mx(size, size, 0);
	fill_mx(m, (t_edge **)&structs->edge, (t_vertex **)&structs->ver);
	structs->mx = m;
	structs->m_size = size;
}