#include "lem_in.h"

int					get_index_of_ver(void **v, char *name, int size)
{
	t_vertex        *tmp;
	int             i;

	i = 0;
	while (i < size)
	{
		tmp = (t_vertex *)v[i];
		if (ft_strequ(tmp->name, name))
			return (i);
		i++;
	}
	ft_printf("\n");
	return (-1);
}

void 				**convert_ver_to_ptrs(t_vertex **ver, int len)
{
	t_vertex 		*v;
	void 			**ptr;
	int 			i;

	i = 0;
	ptr =  ft_new_ptr_array(len);
	v = *ver;
	while (v)
	{
		ptr[i] = v;
		i++;
		v = v->next;
	}
	return (ptr);
}

void 				set_indexes_of_ver(t_edge **edge, void **ver, int len)
{
	t_edge			*e;

	e = *edge;
	while (e)
	{
		e->v1_i = get_index_of_ver(ver, e->v1->name, len);
		e->v2_i = get_index_of_ver(ver, e->v2->name, len);
		e = e->next;
	}
}