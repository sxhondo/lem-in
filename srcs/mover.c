#include "lem_in.h"

static void		make_movement(t_list **lst, t_vertix **ver, int wave)
{
	t_list		*l;
	t_path		*p;

	l = *lst;
	p = l->content;
	p += 6;
	ft_printf("%s", get_i_ver(ver, p->node));
	exit (0);



}

void			mover(int ants, t_list **lst, t_vertix **ver)
{
	t_list		*l;
	int 		i;
	int 		wave;

	ft_printf("{cyan}ANTS: %d\n{eoc}", ants);
	print_paths(lst, ver);
	ft_printf("\n");
	i = ants - ft_lstlen(lst);
	wave = 0;
	while (i)
	{
		i = ants - ft_lstlen(lst);
		make_movement(lst, ver, wave);
	}
	ft_printf("[%d]", i);
}