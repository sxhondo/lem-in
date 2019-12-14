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

	i = -1;
	m = structs->mx;
	while (++i < structs->m_size)
		free(m[i]);
	free(structs->mx);
	free_list((t_list **)&structs->paths);
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


static unsigned 	parse_arguments(int ac, char **arg)
{
	unsigned 		flag;
	int 			i;

	flag = 0;
	i = 1;
	while (i < ac)
	{
		if (ft_strequ(arg[i], "-c"))
			flag |= COLORS;
		if (ft_strequ(arg[i], "-d"))
			flag |= DEBUG;
		i++;
	}
	return (flag);
}

int 				main(int ac, char **av)
{
	unsigned 		flags = 0;
	t_structs		*structs;

	structs = init_structs();
	reader(structs, av[2]);
	check_lists((t_vertex **)&structs->ver, (t_edge **)&structs->edge);
	create_matrix(structs);
	structs->paths = solver(structs->mx, structs->m_size, (t_vertex **)&structs->ver);
	structs->ants = spawn_ants(structs->ants_amount, (t_list **)&structs->paths);
	flags = parse_arguments(ac, av);
	if (flags & DEBUG)
		print_all(structs);
	mover((t_vertex **)&structs->ver, (t_ants **)&structs->ants, flags);
	free_structs(structs);
	return (0);
}
