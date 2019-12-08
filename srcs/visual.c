#include "incs/lem_in.h"

int					re_draw(t_vis *vis)
{
	int 			i;
	int 			last;
	t_list			*t;
	t_vertix		*v;

	mlx_clear_window(vis->mlx, vis->win);
	draw_graph(vis);
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
		v = find_ver_by_index(vis->ver, ((int *)t->content)[i]);
		mlx_put_image_to_window(vis->mlx, vis->win, vis->skin, v->x, v->y);
		i++;
	}
	*vis->turns = ((t_list *)*vis->turns)->next;
	return (0);
}

static int 			start_animation(t_vis *vis)
{
	if (*vis->turns)
	{
		re_draw(vis);
	}
	usleep(500000);
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