#include "incs/lem_in.h"

static void 		convert(t_vertix **ver, t_edge **edge,
	void **me, int ve)
{
	t_list 		*a;
	t_list 		*b;
	t_vertix	*v;
	t_edge 		*e;
	int 		*tab;

	tab = ft_new_array(2, 0);
	v = find_ver_by_index(ver, ve);
	tab[0] = v->x;
	tab[1] = v->y;
	ft_printf("%s: %d - %d", v->name, tab[0], tab[1]);
	if (!(a = ft_lstnew(tab, sizeof(int) * 2)))
		put_error(12, 0, NULL);
	ft_lstpushback((t_list **)&me[0], a);
	// e = find_edge_by_name(edge, v->name);
	// tab[0] = e->x;
	// tab[1] = e->y;
	// if (!(b = ft_lstnew(tab, sizeof(int) * 2)))
	// 	put_error(12, 0, NULL);
	// ft_lstpushback((t_list **)&me[1], b);
}

void				place_ants(t_vis *vis, void **me)
{
	int 			i;
	int 			last;
	t_list			*t;
	t_vertix		*v;
	t_edge 			*e;
	int 			*tmp;

	t = *vis->turns;
	i = 0;
	while (i < vis->amount)
	{
		if (((int *)t->content)[i] == -1)
		{
			last = ver_len(vis->ver) - 1;
			v = find_ver_by_index(vis->ver, last);
			mlx_put_image_to_window(vis->mlx, vis->win, vis->skin, v->x, v->y);
			i++;
			continue ;
		}
		convert(vis->ver, vis->edge, me, ((int *)t->content)[i]);
		i++;
	}
	*vis->turns = ((t_list *)*vis->turns)->next;
}

static int 			start_animation(t_vis *vis)
{
	t_list 			*a = NULL;
	t_list 			*b = NULL;
	void 			**me;

	me = new_ptr_array(2);
	me[0] = a;
	me[1] = b;
	if (*vis->turns)
	{
		place_ants(vis, me);
		for (t_list *ai = (t_list *)me[0]; ai; ai = ai->next)
		{
			ft_printf("END: x:%d y:%d\n",
			((int *)ai->content)[0], ((int *)ai->content)[1]);

		}
		exit (0);
		// for (t_list *ai = (t_list *)me[0]; ai; ai = ai->next)
		// {
		// 	mlx_clear_window(vis->mlx, vis->win);
		// 	draw_graph(vis);
		// 	mlx_put_image_to_window(vis->mlx, vis->win, vis->skin,
		// 		((int *)ai->content)[0], ((int *)ai->content)[1]);
		// }
	usleep(500000);
	}
}

int 				key_handle(int code, t_vis *vis)
{
//	ft_printf("[%d]\n", code);
	if (code == 12 || code == 113)
	{

		mlx_loop_hook(vis->mlx, start_animation,  vis);
	}
	if (code == 7 || code == 120)
	{
		ft_lstfree(&vis->t_begin);
		vertix_free(vis->ver);
		edge_free(vis->edge);
		mlx_clear_window(vis->mlx, vis->win);
		mlx_destroy_image(vis->mlx, vis->skin);
		mlx_destroy_image(vis->mlx, vis->back);
		free(vis);
		exit (0);
	}
}
