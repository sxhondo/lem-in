#include "incs/lem_in.h"

void			print_mx(int **mx, int size, t_vertix **ver)
{
	int 		i, j;
	t_vertix 	*p;

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

void		free_mx(t_mx *M)
{
	int 	i;

	i = 0;
	while (i < M->size)
		free(M->mx[i++]);
	free (M->mx);
	free (M);
}