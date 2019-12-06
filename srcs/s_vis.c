#include "lem_in.h"

const int 			width = 800;
const int 			height = 600;

static void				put_pixel(t_vis *vis, char *data, unsigned color)
{
	if (vis->en == 0)
	{
		*data++ = (char)(color);
		*data++ = (char)(color >> 8u);
		*data = (char)(color >> 16u);
	}
	else if (vis->en == 1)
	{
		*data++ = (char)(color >> 16u);
		*data++ = (char)(color >> 8u);
		*data = (char)(color);
	}
}

t_vertix      *find_ver(t_vertix **ver, char *name)
{
	t_vertix    *v;
	v = *ver;
	while (v)
	{
		if (ft_strequ(v->name, name))
			return (v);
		v = v->next;
	}
	return (0);
}

static void				place_square(t_vis *vis, int x, int y, unsigned color)
{
	int 				r = 25;
	int 				i;

	i = y - r - 1;
	while (++i <= y + r)
	{
		put_pixel(vis, vis->data +
					   (i * vis->sl) + ((x - r) * (vis->bpp / 8)), color);
		put_pixel(vis, vis->data +
					   (i * vis->sl) + ((x + r) * (vis->bpp / 8)), color);
	}
	i = x - r - 1;
	while (++i <= x + r)
	{
		put_pixel(vis, vis->data +
					   ((y - r) * vis->sl) + (i * (vis->bpp / 8)), color);
		put_pixel(vis, vis->data +
					   ((y + r + 1) * vis->sl) + (i * (vis->bpp / 8)), color);
	}
}

static void			draw_square(t_vis *vis)
{
	t_vertix		*ver;

	ver = *vis->ver;
	while (ver)
	{
		place_square(vis, ver->x, ver->y, 0xFF00FF);
		ver = ver->next;
	}
}

static void				swap(int *a, int *b)
{
	int 				tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void				draw_connections(t_vis *vis, int x1, int y1, int x2, int y2)
{
	int 				x;
	int 				y;
	int 				dx;
	int 				dy;
	int 				p;

	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	p = (2 * dy) - dx;
	while (x <= x2)
	{
		mlx_pixel_put(vis->mlx, vis->win, x, y, 0xFF00FF);
		x++;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * dy) - 2 * dx;
			y++;
		}
	}
}

void				draw_graph(t_vis *vis)
{
	t_vertix		*ver;
	t_edge			*edge;

	draw_square(vis);
	ver = *vis->ver;
	edge = *vis->edge;
	while (edge)
	{
		draw_connections(vis, find_ver(&ver, edge->e1)->x, find_ver(&ver, edge->e1)->y,
				  find_ver(&ver, edge->e2)->x, find_ver(&ver, edge->e2)->y);
		edge = edge->next;
	}
//	mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
}

int 				refresh(int code, t_vis *vis)
{
	if (code == 6)
	{
		mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
	}
	if (code == 7)
	{
		exit (0);
	}
}

t_vis     			*init_mlx(t_vertix **ver, t_edge **edge, t_steps **steps, int amount)
{
	t_vis   		*vis;

	if (!(vis = ft_memalloc(sizeof(t_vis))))
		return (put_error(12, 0, NULL));
	vis->mlx = mlx_init();
	vis->win = mlx_new_window(vis->mlx, width, height, "lem-in");
	vis->back = mlx_new_image(vis->mlx, width, height);
	vis->data = mlx_get_data_addr(vis->back, &vis->bpp, &vis->sl, &vis->en);
	vis->skin = mlx_xpm_file_to_image(vis->mlx, "skin/rat.xpm",
			&vis->skin_w, &vis->skin_h);
	vis->ver = ver;
	vis->edge = edge;
	vis->steps = steps;
	vis->amount = amount;
	draw_graph(vis);

//	mlx_key_hook(vis->win, refresh, vis);
	mlx_loop(vis->mlx);
	return (vis);
}
