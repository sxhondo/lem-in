#include <mlx.h>
#include <stdlib.h>
#include "lem_in.h"

#define	FLOW 		nums[0]
#define	MAX_WAVE 	nums[1]
#define LAST		nums[2]

int 				all_finished(t_ants **ants, int finish)
{
	t_ants			*a;

	a = *ants;
	while (a)
	{
		if (a->pos != finish && a->pos != INT32_MAX)
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

void				mover(int amount, t_list **lst, t_vertix **ver, t_edge **edge)
{
	int 			i;
	int 			tmp;
	int 			nums[3];
	t_ants		*ants;
	t_ants		*tmpr;
	t_vis 		*vis;

	ants = spawn_ants(amount);
	FLOW = ft_lstlen(lst) < amount ? ft_lstlen(lst) : amount;
	MAX_WAVE = FLOW;
	LAST = get_last_node((t_path **)&(*lst)->content);
	i = 1;

	vis = init_mlx((t_ants **)ants, ver, edge);
	draw_start(vis);
	mlx_key_hook(vis->win, handle_keys, vis);

	go_forward(ants, lst, ver, i++);
	print_ants(&ants, ver, LAST);

	while (!all_finished(&ants, LAST))
	{

		tmp = update_waves(&ants, lst, ver, i++, MAX_WAVE, FLOW);
		if ((tmpr = get_i_ant(&ants, MAX_WAVE)))
		{
			go_forward(tmpr, lst, ver, tmp);
			MAX_WAVE += FLOW;
		}
		print_ants(&ants, ver, LAST);
	}
	free_ants(&ants);
	mlx_loop(vis->mlx);
}
