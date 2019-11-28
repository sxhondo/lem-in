#include "lem_in.h"

int 				main(int ac, char **av)
{
	t_mx			*M;
	t_vertix		**ver_list;
	void			**mx_ver;

	mx_ver = parser(av[1]);
	M = mx_ver[0];
	ver_list = (t_vertix **)&mx_ver[1];
	print_mx(M->mx, M->size, ver_list);
	solver(M, ver_list);
	print_mx(M->mx, M->size, ver_list);

	vertix_free(ver_list);
	free_mx(M);
	free(mx_ver);
	return (0);
}