#include "lem_in.h"

int 				main(int ac, char **av)
{
	t_mx			*M;
	t_vertix		**ver_list;
	void			**mx_ver;
	t_list			*fin_paths;
	int 			ants;

	mx_ver = parser(av[1]);
	ants = (int)mx_ver[2];
	M = mx_ver[0];
	ver_list = (t_vertix **)&mx_ver[1];
	fin_paths = solver(M, ver_list);

//	ft_printf("{red}final paths: {eoc}\n");
//	print_paths(&fin_paths, ver_list);

	mover(ants, &fin_paths, ver_list);

	vertix_free(ver_list);
	free_mx(M);
	free(mx_ver);
	free_list(&fin_paths);
	return (0);
}
