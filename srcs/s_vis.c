#include "lem_in.h"

const int 			width = 800;
const int 			height = 600;

static void				put_pixel(t_vis *vis, int x, int y, int color)
{
	int 				i;

	i = (x * vis->bpp / 8) + (y * vis->sl);
	if (vis->en == 0)
	{
		vis->data[i] = color;
		vis->data[++i] = color >> 8u;
		vis->data[++i] = color >> 16u;
	}
	else if (vis->en == 1)
	{
		vis->data[i] = color >> 16u;
		vis->data[++i] = color >> 8u;
		vis->data[++i] = color;
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
	int 				tmp;
	int 				r = 25;
	int 				i;

	put_pixel(vis, x, y, color);
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
		ver->x = ver->x > width - 25 ? width - 25 - 1 : ver->x;
		ver->y = ver->y > height - 25 ? height - 25 - 1 : ver->y;
		if (ver->mod == 1)
			color = 0x00FF00;
		else if (ver->mod == 2)
			color = 0xFF0000;
		else
			color = 0xFF00FF;
		place_square(vis, ver->x, ver->y, color);
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

void				draw_graph(t_vis *vis)
{
	t_vertix		*ver;
	t_edge			*edge;

	draw_square(vis);
	ver = *vis->ver;
	edge = *vis->edge;
	while (edge)
	{
		draw_connections(vis, find_ver(&ver, edge->e1)->x,
		find_ver(&ver, edge->e1)->y,  find_ver(&ver, edge->e2)->x,
			find_ver(&ver, edge->e2)->y);
		edge = edge->next;
	}
	mlx_put_image_to_window(vis->mlx, vis->win, vis->back, 0, 0);
}

void 				make_step(t_vis *vis)
{
	t_vertix		*v;
	t_steps			*s;
	t_steps 		*next;
	int 			i;

	i = 0;
	mlx_clear_window(vis->mlx, vis->win);
	draw_graph(vis);
	s = *vis->steps;
	while (s && i < vis->amount)
	{
		if (s->ids[i] >= 0)
		{
			ft_printf("%d\n", s->ids[i]);
			v = get_ver(vis->ver, s->ids[i]);
			ft_printf("x: %d y: %d\n", v->x, v->y);
			mlx_put_image_to_window(vis->mlx, vis->win, vis->skin, v->x, v->y);
		}
		i++;
	}
	if (s)
	{
		next = s->next;
		*vis->steps = next;
	}

}

int 				refresh(int code, t_vis *vis)
{
	int 			i;

	ft_printf("[%d]\n", code);
	if (code == 113) //Q
	{
		make_step(vis);
	}
	if (code == 6 || code == 122) //Z
	{
		// mlx_clear_window(vis->mlx, vis->win);
	}
	if (code == 7 || code == 120) //X
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

	mlx_key_hook(vis->win, refresh, vis);
	mlx_loop(vis->mlx);
	return (vis);
}
