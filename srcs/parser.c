#include "incs/lem_in.h"

//#define 	ANTS			ptrs[0]
//#define 	ANTS_C			(void *)ptrs[0]
//#define		VER_LIST		ptrs[1]
//#define		VER_LIST_C		(t_vertix **)&VER_LIST
//#define		EDGE_LIST		ptrs[2]
//#define 	EDGE_LIST_C		(t_edge **)&EDGE_LIST

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

	put_to_start(ver);
	put_to_end(ver);
	size = ver_len(ver);
	mx = allocate_mx(size, size);
	fill_mx(mx, edge, ver);
	if (!(M = ft_memalloc(sizeof(t_mx))))
		return (put_error(12, 0, NULL));
	M->mx = mx;
	M->size = size;
	return (M);

}

t_info				*init_info()
{
	t_info			*i;

	if (!(i = ft_memalloc(sizeof(t_info))))
		return (put_error(12, 0, NULL));
	i->fd = open("maps/pdf", O_RDONLY);
	i->flag = 0;
	i->mod = 0;
	i->lc = 1;
	i->total = 0;
	return (i);
}

void 				**parser()
{
	t_info			*inf;
	void			**structs;
	void			**ret;
	t_mx			*M;

	inf = init_info();
	structs = new_ptr_array(3);
	reader(structs, inf);

//	M = make_matrix(ANTS, VER_LIST_C, EDGE_LIST_C);
//	ret = new_ptr_array(4);
//	ret[0] = ANTS_C;
//	ret[1] = VER_LIST;
//	ret[2] = EDGE_LIST;
//	ret[3] = M;
//	free(ptrs);
//	return (ret);
}
