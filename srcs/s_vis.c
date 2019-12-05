#include "lem_in.h"

const int 			width = 800;
const int 			height = 600;

void				put_pixel(t_vis *vis, char *data, unsigned color)
{
//	ft_printf("endian: [%d]\n", vis->en);
//	if (vis->en == 0)
//	{
		*data++ = (char)(color);
		*data++ = (char)(color >> 8u);
		*data = (char)(color >> 16u);
//	}
}

void				draw_background(t_vis *vis)
{
	int 			y;
	int 			x;

	y = -1;
	while (++y <= height)
	{
		x = -1;
		while (++x <= width)
			put_pixel(vis, vis->data + (x * (vis->bpp / 8)),
					0xC0C0C0);
		vis->data += vis->sl;
	}
}

int 				refresh(t_vis *vis)
{
	mlx_clear_window(vis->mlx, vis->win);
	draw_background(vis);
//	mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
}

t_vis     			*init_mlx(t_vertix **ver, t_edge **edge, t_steps **steps, int amount)
{
	t_vis   		*vis;

	if (!(vis = ft_memalloc(sizeof(t_vis))))
	{
		put_error(12, 0, NULL);
		return (NULL);
	}
	vis->mlx = mlx_init();
	vis->win = mlx_new_window(vis->mlx, width, height, "prog");
	vis->back = mlx_new_image(vis->mlx, width, height);
	vis->data = mlx_get_data_addr(vis->back, &vis->bpp, &vis->sl, &vis->en);
	vis->skin = mlx_xpm_file_to_image(vis->mlx, "skin/rat.xpm", &vis->skin_w,
									  &vis->skin_h);
	vis->ver = ver;
	vis->edge = edge;
	vis->steps = steps;
	vis->amount = amount;

	draw_background(vis);
	mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
	mlx_put_image_to_window(vis->mlx, vis->win, vis->skin, 12, 12);

	mlx_loop_hook(vis->mlx, &refresh, vis);
	mlx_loop(vis->mlx);

	return (vis);
}
