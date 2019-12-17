#include "lem_in.h"

void			free_list(t_list **tab)
{
	t_list		*lst;
	t_list		*next;
	t_path		*ptr;

	lst = *tab;
	while (lst)
	{
		next = lst->next;
		ptr = lst->content;
		path_free(&ptr);
		free(lst);
		lst = next;
	}
	*tab = NULL;
}

static void			free_structs(t_structs *structs)
{
	int 			i;
	int 			**m;

	vertex_free((t_vertex **)&structs->ver);
	edge_free((t_edge **)&structs->edge);
	free_list((t_list **)&structs->ways);
	free_ants(&structs->ants);
	free(structs);
}

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

int 				main(int ac, char **av)
{
	unsigned 		flags = 0;
	t_structs		*structs;

	flags = parse_arguments(ac, av);
	structs = init_structs();
	reader(structs, flags, av[3]);
	parse_lists((t_vertex **)&structs->ver, (t_edge **)&structs->edge);
	structs->ways = solver((t_edge **)&structs->edge, (t_vertex **)&structs->ver);
	structs->ants = spawn_ants(structs->ants_amount, (t_list **)&structs->ways);
	if (flags & DEBUG)
		print_all(structs);
	mover((t_ants **)&structs->ants, flags);
	free_structs(structs);
	return (0);
}
