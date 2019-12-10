#include "lem_in.h"

int 				all_finished(t_ants **ants, int finish)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos != finish && a->pos != -1)
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

static void			go_forward(t_ants *ants, t_list **lst, int i)
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

int				update_waves(t_ants **ants, t_list **lst, t_vertex **ver, int i,
													int max_wave, int flow)
{
	int 		wave;
	int 		tmp;
	t_ants		*tmpr;

	tmp = i;
	wave = 0;
	while (wave < max_wave)
	{
		tmpr = get_i_ant(ants, wave);
		go_forward(tmpr, lst, tmp);
		wave += flow;
		tmp--;
	}
	return (tmp);
}

static void			print_ants(t_ants **ants, t_vertex **ver, int last)
{
	t_ants			*p;

	p = *ants;
	while (p)
	{
		if (p->pos != 0 && p->pos != -1)
		{
			ft_printf("L%d-%s ", p->id,
					find_ver_by_index(ver, p->pos)->name);
		}
		if (p->pos == last)
			p->pos = -1;
		p = p->next;
	}
	ft_printf("\n");
}

t_ants 				*mover(int amount, t_vertex **ver, t_list **paths)
{
	t_ants			*ants;
	int 			i;
	int 			flow;
	int 			max_wave;
	int 			last;
	int 			tmp;
	t_ants			*tmpr;

	ants = spawn_ants(amount);
	flow = MIN(ft_lstlen(paths), amount);
	max_wave = flow;
	last = get_last_node(paths);
	i = 1;
	go_forward(ants, paths, i++);
	print_ants(&ants, ver, last);
	while (!all_finished(&ants, last))
	{
		tmp = update_waves(&ants, paths, ver, i++, max_wave, flow);
		if ((tmpr = get_i_ant(&ants, max_wave)))
		{
			go_forward(tmpr, paths, tmp);
			max_wave += flow;
		}
		print_ants(&ants, ver, amount);
	}
	free_ants(&ants);
	return (ants);
}