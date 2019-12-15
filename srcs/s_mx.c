//#include "lem_in.h"
//
//int			exclude_overlap(int **mx, int size)
//{
//	int 	i;
//	int 	j;
//
//	i = 0;
//	while (i < size)
//	{
//		j = 0;
//		while (j < size)
//		{
//			if (mx[i][j] == 1 && mx[j][i] == 1)
//			{
//				mx[i][j] = 0;
//				mx[j][i] = 0;
//			}
//			j++;
//		}
//		i++;
//	}
//	return (1);
//}
//
//void		set_to_zero(int **mx, int size)
//{
//	int 	i;
//	int 	j;
//
//	i = 0;
//	while (i < size)
//	{
//		j = 0;
//		while (j < size)
//		{
//			mx[i][j] = 0;
//			j++;
//		}
//		i++;
//	}
//}
//
//static void				fill_mx(int **mx, t_edge **edge, t_vertex **ver)
//{
//	t_edge 				*e;
//
//	e = *edge;
//	while (e)
//	{
//		mx[get_i_by_name(ver, e->v1)][get_i_by_name(ver, e->v2)] = 1;
//		mx[get_i_by_name(ver, e->v2)][get_i_by_name(ver, e->v1)] = 1;
//		e = e->next;
//	}
//}
//
//void 					acreate_matrix(t_structs *structs)
//{
//	int 				**m;
//	int 				size;
//
//	size = vertex_len((t_vertex **)&structs->ver);
//	m = ft_allocate_mx(size, size, 0);
//	fill_mx(m, (t_edge **)&structs->edge, (t_vertex **)&structs->ver);
//	structs->mx = m;
//	structs->m_size = size;
//}
