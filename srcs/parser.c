#include "lem_in.h"

#define 	ANTS				ptrs[0]
#define		VER_LIST		(t_vertix **)&ptrs[1]
#define		EDGE_LIST		(t_edge **)&ptrs[2]

int				**allocate_mx(int x, int y)
{
	int 		i;
	int 		j;
	int 		**mx;

	if (!(mx = (int **)malloc(x * sizeof(int *))))
	{
		put_error(12, 0, NULL);
		return (NULL);
	}
	i = -1;
	while (++i < x)
		if (!(mx[i] = ft_new_array(y, 0)))
			put_error(12, 0, NULL);
	return (mx);
}

static int				iter_to_vertix(t_vertix **ver, char *name)
{
	t_vertix			*v;
	int 				i;

	i = 0;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (i);
		v = v->next;
		i++;
	}
	return (-1);
}

static void				fill_mx(int **mx, t_edge **edge, t_vertix **ver)
{
	t_edge 				*e;

	e = *edge;
	while (e)
	{
		mx[iter_to_vertix(ver, e->e1)][iter_to_vertix(ver, e->e2)] = 1;
		mx[iter_to_vertix(ver, e->e2)][iter_to_vertix(ver, e->e1)] = 1;
		e = e->next;
	}
}

static t_mx				*make_matrix(void *ants, t_vertix **ver, t_edge **edge)
{
	t_mx				*M;
	int 				**mx;
	int 				size;

//	ft_printf("number of ants: {cyan}%5d\n{eoc}", ants);
//	vertix_print(ver);
//	edge_print(edge);
	put_to_start(ver);
	put_to_end(ver);
	size = lst_len((void *)ver, 0);
	mx = allocate_mx(size, size);
	fill_mx(mx, edge, ver);
	if (!(M = ft_memalloc(sizeof(t_mx))))
	{
		put_error(12, 0, NULL);
		return (NULL);
	}
	M->mx = mx;
	M->size = size;
	return (M);

}

void 				**parser(char *path)
{
	int 			fd;
	void			**ptrs;
	void			**ret;
	t_mx			*M;

	ptrs = new_ptr_array(3);

	fd = open(path, O_RDONLY);
	reader(fd, ptrs);
//	reader(0, ptrs);
	M = make_matrix(ANTS, VER_LIST, EDGE_LIST);
/*
	vertix_print(VER_LIST);
	edge_print(EDGE_LIST);
*/
	// edge_free(EDGE_LIST);
	ret = new_ptr_array(4);
	ret[0] = (void *)ptrs[0];
	ret[1] = ptrs[1];
	ret[2] = ptrs[2];
	ret[3] = M;
	free(ptrs);
//	close(fd);
	return (ret);
}
