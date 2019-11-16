#include "lem_in.h"

int 		**make_matrix(int size)
{
	int 	i, j;
	int 	**mx;

	/* two paths */
//	int 	m[4][4] = {
//			/* A */	{0, 1, 1, 0},
//			/* B */	{1, 0, 1, 1},
//			/* C */	{1, 1, 0, 1},
//			/* D */	{0, 1, 1, 0},
//	};

	/* no paths */
//	int 	m[4][4] = {
//			/* A */	{0, 1, 1, 0},
//			/* B */	{1, 0, 0, 0},
//			/* C */	{1, 0, 0, 0},
//			/* D */	{0, 0, 1, 0},
//	};

	/* two paths with one common node ! ! ! */
//	int 	m[5][5] = {
//			/* A */	{0, 1, 1, 0, 0},
//			/* B */	{1, 0, 0, 1, 0},
//			/* C */	{1, 0, 0, 1, 0},
//			/* D */	{0, 1, 1, 0, 1},
//			/* E */	{0, 0, 0, 1, 0},
//	};

//	int 	m[5][5] = {
//			/* A */	{0, 1, 0, 0, 0},
//			/* B */	{0, 0, 1, 1, 0},
//			/* C */	{0, 1, 0, 1, 0},
//			/* D */	{0, 1, 0, 0, 1},
//			/* E */	{0, 0, 0, 1, 0},
//	};

	int 	m[8][8] = {
			/* A */	{0, 1, 1, 0, 0, 0, 0, 0},
			/* B */	{1, 0, 0, 1, 0, 0, 0, 0},
			/* C */ {1, 0, 0, 0, 1, 1, 0, 0},
			/* D */ {0, 1, 0, 0, 1, 0, 0, 0},
			/* E */ {0, 0, 1, 1, 0, 1, 0, 1},
			/* F */ {0, 0, 1, 0, 1, 0, 1, 0},
			/* G */ {0, 0, 0, 0, 0, 1, 0, 1},
			/* H */ {0, 0, 0, 0, 1, 0, 1, 0},
	};


	mx = (int **)malloc(size * sizeof(int *));
	for (i = 0; i < size; i++)
		mx[i] = (int *)malloc(size * sizeof(int));

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			mx[i][j] = m[i][j];
	}
	return (mx);
}

void		print_matrix(int **mx, int size)
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
		ft_printf("{green}%c{eoc}", ch++);
		j = -1;
		while (++j < size)
			ft_printf("%3d", mx[i][j]);
		ft_printf("\n");
	}
	ft_printf("\n");
}

void		free_matrix(int **mx, int size)
{
	int 	i;

	i = 0;
	while (i < size)
		free(mx[i++]);
	free (mx);
}