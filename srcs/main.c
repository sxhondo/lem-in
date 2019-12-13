#include "lem_in.h"

void				ants_print(t_ants **ants, t_vertex **ver)
{
	t_ants			*an;

	an = *ants;
	while (an)
	{
		ft_printf("{red}id:[%d]\t", an->id);
		ft_printf(" {cyan}path: %d\t", an->path);
		if (an->pos)
		{
			ft_printf("{green} pos: %d",  an->pos->node);
			ft_printf("{green} (%s)\n",
					  find_ver_by_index(ver, an->pos->node)->name);
		}
		else
			ft_printf("{magenta} finished! {eoc}\n");
		an = an->next;
	}
	ft_printf("\n");
}

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

void				print_all(t_structs *str)
{
	ft_printf("{cyan}%d\n{eoc}", str->ants_amount);
	vertex_print((t_vertex **)&str->ver);
	edge_print((t_edge **)&str->edge);
	print_mx(str->mx, str->m_size, (t_vertex **)&str->ver);
	paths_print(&str->paths, (t_vertex **)&str->ver);
	ants_print((t_ants **)&str->ants, (t_vertex **)&str->ver);
}

int 				main(int ac, char **av)
{
	t_structs		*structs;

	structs = init_structs();
	reader(structs, av[1]);
	check_lists((t_vertex **)&structs->ver, (t_edge **)&structs->edge);
	create_matrix(structs);
	structs->paths = solver(structs->mx, structs->m_size, (t_vertex **)&structs->ver);
	structs->ants = spawn_ants(structs->ants_amount, (t_list **)&structs->paths);
	print_all(structs);
	mover((t_vertex **)&structs->ver, (t_ants **)&structs->ants);
	free_structs(structs);
	return (0);
}
