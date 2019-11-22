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

//	int 	m[4][4] = {
//			/* A */	{0, 1, 1, 0},
//			/* B */	{0, 0, 0, 1},
//			/* C */	{0, 0, 0, 1},
//			/* D */	{0, 0, 1, 0},
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

int 		**duplicate_matrix(int **mx, int size)
{
	int 	i, j;
	int 	**new;

	new = (int **)malloc(size * sizeof(int *));
	for (i = 0; i < size; i++)
		new[i] = (int *)malloc(size * sizeof(int));

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			new[i][j] = mx[i][j];
	}
	return (new);
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

void		set_mx_to(int **mx, int size, int c)
{
	int 	i, j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (mx[i][j] == 0 || mx[i][j] == 1 || mx[i][j] == -1)
				mx[i][j] = c;
			j++;
		}
		i++;
	}
	mx[0][0] = 0;
}

int 		count_max_edges(int **mx, int size)
{
	int 	count;
	int 	i;
	int 	j;

	count = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (mx[i][j] != 0)
				count++;
			j++;
		}
		i++;
	}
	return (count);
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

void		free_matrix(int **mx, int size)
{
	int 	i;

	i = 0;
	while (i < size)
		free(mx[i++]);
	free (mx);
}
