#include "incs/lem_in.h"

#define	FLOW 		nums[0]
#define	MAX_WAVE 	nums[1]
#define LAST		nums[2]

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

int				update_waves(t_ants **ants, t_list **lst, t_vertix **ver, int i,
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

void 				collect_turns(t_list **turns, t_ants **ants, int amount)
{
	t_ants			*a;
	t_list			*tmp;
	int 			*tab;

	tab = ft_new_array(amount ,0);
	a = *ants;
	while (a)
	{
		tab[a->id - 1] = a->pos;
		a = a->next;
	}
	tmp = ft_lstnew(tab, sizeof(int) * amount);
	ft_lstpushback(turns, tmp);
}

void			print_ants(t_ants **ants, t_vertix **ver, t_list **turns,
														int last, int amount)
{
	t_ants		*p;

	p = *ants;
	while (p)
	{
		if (p->pos != 0 && p->pos != -1)
		{
			ft_printf("L%d-%s ", p->id, find_ver_by_index(ver, p->pos)->name);
		}
		if (p->pos == last)
			p->pos = -1;
		p = p->next;
	}
	collect_turns(turns, ants, amount);
	ft_printf("\n");
}


t_list 				*mover(int amount, t_list **lst, t_vertix **ver, t_edge **edge)
{
	int 			i;
	int 			tmp;
	int 			nums[3];
	t_ants			*ants;
	t_ants			*tmpr;
	t_list 			*steps = NULL;

	ants = spawn_ants(amount);
	FLOW = ft_lstlen(lst) < amount ? ft_lstlen(lst) : amount;
	MAX_WAVE = FLOW;
	LAST = get_last_node((t_path **)&(*lst)->content);
	i = 1;
	go_forward(ants, lst, ver, i++);
	print_ants(&ants, ver, &steps, LAST, amount);
	while (!all_finished(&ants, LAST))
	{
		tmp = update_waves(&ants, lst, ver, i++, MAX_WAVE, FLOW);
		if ((tmpr = get_i_ant(&ants, MAX_WAVE)))
		{
			go_forward(tmpr, lst, ver, tmp);
			MAX_WAVE += FLOW;
		}
		print_ants(&ants, ver, &steps, LAST, amount);
	}
	free_ants(&ants);
	return (steps);
}
