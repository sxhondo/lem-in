#include "incs/lem_in.h"


static void			re_draw(t_vis *vis)
{
	mlx_clear_window(vis->mlx, vis->win);
	draw_graph(vis);
}

/*
static int 			start_animation(t_vis *vis)
{
	t_vertix		*v;
	int 			i;
	int 			*end;

	i = 0;
	end = vis->t_prev;
	for (int q = 0; q < vis->amount; q++)
		ft_printf("%d ", end[q]);
	while (i < vis->amount)
	{
		if ((v = find_ver_by_index(vis->ver, end[i])))
		{
			mlx_put_image_to_window(vis->mlx, vis->win, vis->skin, v->x, v->y);
		}
		i++;
	}
}
*/

static int 			middle_animation(t_vis *vis)
{
	int 			*prev;
	int 			*curr;
	t_vertix		*v1;
	t_vertix		*v2;
	int 			i;


	i = 0;
	if (*vis->turns == NULL)
		return (0);
	prev = vis->t_prev;
	curr = ((t_list *)*vis->turns)->content;
	while (i < vis->amount)
	{
		if (prev[i] != curr[i])
		{
			v1 = find_ver_by_index(vis->ver, prev[i]);
			if (!(v2 = find_ver_by_index(vis->ver, curr[i])))
				v2 = find_ver_by_index(vis->ver, ver_len(vis->ver) - 1);
			mlx_put_image_to_window(vis->mlx, vis->win, vis->skin,
					(v1->x + v2->x) / 2, (v1->y + v2->y) / 2);
		}
		i++;
	}
	vis->t_prev = curr;
	*vis->turns = ((t_list *)*vis->turns)->next;

}

int 				animation1(t_vis *vis)
{
	re_draw(vis);
	middle_animation(vis);
	usleep(900000);
}

int 				key_handle(int code, t_vis *vis)
{
	if (code == 12 || code == 113)
	{
		mlx_loop_hook(vis->mlx, animation1, vis);
	}
	if (code == 7 || code == 120)
	{
//		lstfree(&vis->t_begin);
		vertix_free(vis->ver);
		edge_free(vis->edge);
		mlx_clear_window(vis->mlx, vis->win);
		mlx_destroy_image(vis->mlx, vis->skin);
		mlx_destroy_image(vis->mlx, vis->back);
		free(vis);
		exit (0);
	}
}
