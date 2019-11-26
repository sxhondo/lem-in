#include "lem_in.h"

static void			manage_ptr_array(void **ptrs)
{
	ft_printf("number of ants: {cyan}%5d\n{eoc}", ptrs[0]);
	vertix_print((t_vertix **)&ptrs[1]);
	vertix_free((t_vertix **)&ptrs[1]);
	edge_print((t_edge **)&ptrs[2]);
	edge_free((t_edge **)&ptrs[2]);
}

int 				main(int ac, char **av)
{
	int 			fd;
	void			**ptrs;

	ptrs = get_structures();
	if ((fd = open(av[1], O_RDONLY)) == -1)
		put_error(0, 0);
	reader(fd, ptrs);
	manage_ptr_array(ptrs);
	free(ptrs);
	close(fd);
}