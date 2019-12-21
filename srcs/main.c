#include "lem_in.h"

static t_structs			*init_structs()
{
	t_structs				*s;

	if (!(s = ft_memalloc(sizeof(t_structs))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	s->edge = NULL;
	s->ver = NULL;
	s->ants_amount = 0;
	return (s);
}

static void			free_structs(t_structs *structs)
{

	if (structs->ver)
		vertex_free((t_vertex **)&structs->ver);
	if (structs->edge)
		edge_free((t_edge **)&structs->edge);
	if (structs->ways)
		free_list((t_list **)&structs->ways);
	if (structs->ants)
		ants_free(&structs->ants);
	free(structs);
}

int 				main(int ac, char **av)
{
	unsigned 		flags;
	t_structs		*structs;

	flags = parse_arguments(ac, av);
	structs = init_structs();
	reader(structs, flags, av[ac - 1]);
	parse_lists((t_vertex **)&structs->ver, (t_edge **)&structs->edge);
	structs->ways = solver(structs->ants_amount,
			(t_edge **)&structs->edge, (t_vertex **)&structs->ver);
	structs->ants = spawn_ants(structs->ants_amount, (t_list **)&structs->ways);
	if (flags & DEBUG)
		print_all(structs);
	mover((t_ants **)&structs->ants, flags);
	free_structs(structs);
	return (0);
}
