#include "lem_in.h"

int 				all_finished(t_ants **ants, int finish)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos != finish)
			return (0);
		a = a->next;
	}
	return (1);
}

static int 			get_i_path(t_path **path, int value)
{
	t_path			*p;

	p = *path;
	while (value--)
	{
		p = p->next;
	}
	return (p->node);
}

static t_ants 		*set_ant(t_ants *ants, int value)
{

	while (value--)
		ants = ants->next;
	return (ants);
}

t_ants				*get_i_ant(t_ants **ants, int value)
{
	t_ants			*a;

	a = *ants;
	if (!*ants)
		return (NULL);
	while (a && value--)
		a = a->next;
	return (a);
}

void				go_forward(t_ants *ants, t_list **lst, t_vertix **ver, int i)
{
	t_list			*l;
	t_path			*p;


	l = *lst;
	while (l)
	{
		p = l->content;
		if (i >= path_len(&p))
			return ;
		if (ants)
		{
			ants->pos = get_i_path(&p, i);
			ants = ants->next;
		}
		l = l->next;
	}
}

int				update_waves(t_ants **ants, t_list **lst, t_vertix **ver, int i, int max_wave, int flow)
{
	int 		wave;
	int 		tmp;
	t_ants		*tmpr;

	tmp = i;
	wave = 0;
	while (wave < max_wave)
	{
		tmpr = get_i_ant(ants, wave);
		go_forward(tmpr, lst, ver, tmp);
		wave += flow;
		tmp--;
	}
	return (tmp);
}

int 				get_last_node(t_path **path)
{
	t_path			*p;

	p = *path;
	while (p->next)
		p = p->next;
	return (p->node);
}

static void			**init_stuff(t_list **lst, t_vertix **ver, int amount)
{
	void			**structs;

	structs = new_ptr_array(3);
	structs[0] = spawn_ants(amount);
	structs[1] = *lst;
	structs[2] = *ver;
	return (structs);
}

void				mover(int amount, t_list **lst, t_vertix **ver)
{
	int 			i;
	int 			tmp;
	int 			max_wave;
	int 			flow;
	int 			last;
	t_ants			*a;
	t_ants			*tmpr;

	a = spawn_ants(amount);
	flow = ft_lstlen(lst) < amount ? ft_lstlen(lst) : amount;
	max_wave = flow;
	last = get_i_path((t_path **)&(*lst)->content,
					  path_len((t_path **)&(*lst)->content) - 1);
	i = 1;
	go_forward(a, lst, ver, i++);
	print_ants(&a, ver, last);
	while (!all_finished(&a, last))
	{
		tmp = update_waves(&a, lst, ver, i, max_wave, flow);
		if ((tmpr = get_i_ant(&a, max_wave)))
		{
			go_forward(tmpr, lst, ver, tmp);
			max_wave += flow;
		}
		i++;
		print_ants(&a, ver, last);
	}
	free_ants(&a);
}