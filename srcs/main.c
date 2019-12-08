#include "incs/lem_in.h"

static t_vis				*init_mlx(t_vertix **ver, t_edge **edge,
													t_list **turns, int amount)
{
	t_vis   				*vis;

	if (!(vis = ft_memalloc(sizeof(t_vis))))
		return (put_error(12, 0, NULL));
	vis->mlx = mlx_init();
	vis->width = 800;
	vis->height = 600;
	vis->win = mlx_new_window(vis->mlx, vis->width, vis->height, "lem-in");
	vis->back = mlx_new_image(vis->mlx, vis->width, vis->height);
	vis->data = mlx_get_data_addr(vis->back, &vis->bpp, &vis->sl, &vis->en);
	vis->skin = mlx_xpm_file_to_image
			(vis->mlx, "skin/rat.xpm", &vis->skin_w, &vis->skin_h);

	vis->ver = ver;
	vis->edge = edge;
	vis->turns = turns;
	vis->t_begin = *turns;
	vis->amount = amount;

	draw_graph(vis);

	mlx_key_hook(vis->win, key_handle, vis);
	mlx_loop(vis->mlx);
	return (vis);
}

int 				main(int ac, char **av)
{
	t_mx			*M;
	t_vertix		**ver;
	t_edge			**edge;
	void 			**data;
	t_list			*fin_paths;
	t_list			*steps;
	size_t 			amount;

	data = parser();
	amount = (size_t)data[0];
	ver = (t_vertix **)&data[1];
	edge = (t_edge **)&data[2];
	M = data[3];
	fin_paths = solver(M, ver);
	steps = mover(amount, &fin_paths, ver, edge);
	free_mx(M);
	if (av[1] && ft_strequ(av[1], "-v"))
		init_mlx(ver, edge, &steps, amount);
	free_list(&fin_paths);
	vertix_free(ver);
	edge_free(edge);
	free(data);
	return (0);
}
