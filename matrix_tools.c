#include "lem_in.h"

t_mx 		*make_mx(int size)
{
//	int 	m[8][8] = {
//			/* A */	{0, 1, 1, 0, 0, 0, 0, 0},
//			/* B */	{1, 0, 0, 1, 0, 0, 0, 0},
//			/* C */ {1, 0, 0, 0, 1, 1, 0, 0},
//			/* D */ {0, 1, 0, 0, 1, 0, 0, 0},
//			/* E */ {0, 0, 1, 1, 0, 1, 0, 1},
//			/* F */ {0, 0, 1, 0, 1, 0, 1, 0},
//			/* G */ {0, 0, 0, 0, 0, 1, 0, 1},
//			/* H */ {0, 0, 0, 0, 1, 0, 1, 0},
//	};

//	 int		m[14][14] = {
//	 		/* A */	{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//	 		/* B */	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	 		/* C */	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	 		/* D */	{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
//	 		/* E */	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//	 		/* F */	{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
//	 		/* G */	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
//	 		/* H */	{0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0},
//	 		/* I */	{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
//	 		/* J */	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
//	 		/* K */	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
//	 		/* L */	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
//	 		/* M */	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//	 		/* N */	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
//	 };

	int		m[6][6] = {
			/* A */	{0, 1, 1, 1, 0, 0},
			/* B */	{1, 0, 1, 1, 0, 0},
			/* C */	{1, 1, 0, 0, 1, 1},
			/* D */	{1, 1, 0, 0, 1, 1},
			/* E */	{0, 0, 1, 1, 0, 1},
			/* F */	{0, 0, 1, 1, 1, 0},
	};

	int 	i, j;
	int 	**mx;
	t_mx	*s;

	if (!(s = ft_memalloc(sizeof(t_mx))))
		return (NULL);

	if (!(mx = (int **)malloc(size * sizeof(int *))))
		return (NULL);

	for (i = 0; i < size; i++)
		mx[i] = (int *)malloc(size * sizeof(int));
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			mx[i][j] = m[i][j];
	}
	s->mx = mx;
	s->size = size;
	return (s);
}

void		print_mx(int **mx, int size)
{
	char 	ch;
	int 	i, j;

	ch = 'A';
	ft_printf("\n ");
	for (i = 0; i < size; i++)
		ft_printf("{red}%3c", ch++);
	ft_printf("\n");
	ch = 'A';
	i = -1;
	while (++i < size)
	{
		ft_printf("{blue}%c{eoc}", ch++);
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

int			*init_tab(int size, int c)
{
	int 	*tab;

	if (!(tab = ft_new_array(size, c)))
		return (0);
	tab[0] = 0;
	return (tab);
}

void		print_tab(int *tab, int size)
{
	int 	i;
	int 	ch = 'A';

	ft_printf("\n");
	for (i = 0; i < size; i++)
		ft_printf("{red}%3c{eoc}", ch++);
	ft_printf("\n");
	for (i = 0; i < size; i++)
		ft_printf("{cyan}%3d{eoc}", tab[i]);
	ft_printf("\n\n");
}