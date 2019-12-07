#include "lem_in.h"

int 				main(int ac, char **av)
{
	t_mx			*M;
	t_vertix		**ver;
	t_edge			**edge;
	void 			**data;
	t_list			*fin_paths;
	size_t 			ants;
	t_list 			**steps;

	data = parser(av[1]);
	ants = (size_t)data[0];
	ver = (t_vertix **)&data[1];
	edge = (t_edge **)&data[2];
	M = data[3];

	fin_paths = solver(M, ver);
	print_paths(&fin_paths, ver);
	steps = mover(ants, &fin_paths, ver, edge);

	for (t_list *p = *steps; p; p = p->next)
	{
		for (t_ants *ptr = p->content; ptr; ptr = ptr->next)
			ft_printf("id: [%d] pos: [%d] ", ptr->id, ptr->pos);
		ft_printf("\n");
	}
	exit (0);
	// init_mlx(ver, edge, &eps, ants);

	// steps_free(&eps);
	vertix_free(ver);
	edge_free(edge);
	free_mx(M);
	free_list(&fin_paths);
	free(data);
	return (0);
}
