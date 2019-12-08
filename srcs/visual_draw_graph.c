#include <incs/lem_in.h>

static void				put_pixel(t_vis *vis, int x, int y, unsigned color)
{
	int 				i;

	i = (x * vis->bpp / 8) + (y * vis->sl);
	if (vis->en == 0)
	{
		vis->data[i] = (char)color;
		vis->data[++i] = (char)(color >> 8u);
		vis->data[++i] = (char)(color >> 16u);
	}
	else if (vis->en == 1)
	{
		vis->data[i] = (char)(color >> 16u);
		vis->data[++i] = (char)(color >> 8u);
		vis->data[++i] = (char)(color);
	}
}

static void				draw_connections(t_vis *vis, int x1, int y1, int x2, int y2)
{
	int 				dx;
	int					dy;
	int					sign_x;
	int					sign_y;
	int 				error;
	int					x, y;

	dx = ABS(x2 - x1);
	dy = ABS(y2 - y1);
	sign_x = x1 < x2 ? 1 : -1;
	sign_y = y1 < y2 ? 1 : -1;
	error = dx - dy;
	x = x1;
	y = y1;
	while (x != x2 || y != y2)
	{
		put_pixel(vis, x, y, 0xFFFFFF);
		if ((error * 2) > -dy)
		{
			error -= dy;
			x += sign_x;
		}
		else
		{
			error += dx;
			y += sign_y;
		}
	}
}

static void				place_square(t_vis *vis, int x, int y, unsigned color)
{
	int 				tmp;
	int 				r = 25;
	int 				i;

	tmp = y - r;
	i = r * 2;
	while (i >= 0)
	{
		put_pixel(vis, x - r , tmp + i, color);
		put_pixel(vis, x + r , tmp + i, color);
		i--;
	}
	tmp = x - r;
	i = r * 2;
	while (i >= 0)
	{
		put_pixel(vis, tmp + i, y - r, color);
		put_pixel(vis, tmp + i, y + r, color);
		i--;
	}
}

static void			draw_square(t_vis *vis)
{
	unsigned		color;
	t_vertix		*ver;

	ver = *vis->ver;
	while (ver)
	{
		ver->x = ver->x < 25 ? 25 : ver->x;
		ver->y = ver->y < 25 ? 25 : ver->y;
		ver->x = ver->x > vis->width - 25 ? vis->width - 25 - 1 : ver->x;
		ver->y = ver->y > vis->height - 25 ? vis->height - 25 - 1 : ver->y;
		if (ver->mod == 1)
			color = 0x00FF00;
		else if (ver->mod == 2)
			color = 0xFF0000;
		else
			color = 0xFF00FF;
		place_square(vis, ver->x, ver->y, color);
		mlx_string_put(vis->mlx, vis->win, ver->x, ver->y, 0x000000, "hey");
		ver = ver->next;
	}
}

void				draw_graph(t_vis *vis)
{
	t_list 			*tab;
	t_vertix		*ver;
	t_vertix 		*v1;
	t_vertix 		*v2;
	t_edge			*edge;

	draw_square(vis);
	ver = *vis->ver;
	edge = *vis->edge;
	while (edge)
	{
		v1 = find_ver_by_name(&ver, edge->e1);
		v2 = find_ver_by_name(&ver, edge->e2);
		draw_connections(vis, v1->x, v1->y, v2->x, v2->y);
		edge->x = (v1->x + v2->x) / 2;
		edge->y = (v1->y + v2->y) / 2;
		edge = edge->next;
	}
	mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
}
