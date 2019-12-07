#include "lem_in.h"

// t_mx 				*convert_steps_to_mx(t_steps **steps)

int 				main(int ac, char **av)
{
	t_mx			*M;
	t_vertix		**ver;
	t_edge			**edge;
	void 			**data;
	t_list			*fin_paths;
	size_t 			ants;
	t_list 			*steps;
	// t_steps 		*steps;

	data = parser(av[1]);
	ants = (size_t)data[0];
	ver = (t_vertix **)&data[1];
	edge = (t_edge **)&data[2];
	M = data[3];

	fin_paths = solver(M, ver);
	print_paths(&fin_paths, ver);
	steps = mover(ants, &fin_paths, ver, edge);


	for (t_list *p = steps; p; p = p->next)
	{
		for (int i = 0; i < ants; i++)
		{
			ft_printf("%d ", ((int *)p->content)[i]);
		}
		ft_printf("\n");
	}


//	init_mlx(ver, edge, &steps, ants);
	ft_lstfree(&steps);
	vertix_free(ver);
	edge_free(edge);
	free_mx(M);
	free_list(&fin_paths);
	free(data);
	return (0);
}
