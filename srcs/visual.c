#include <mlx.h>
#include <stdlib.h>
#include "lem_in.h"

void      draw_square(t_vis *vis, int x, int y, int r, unsigned co)
{
  int     i;
  int     color = 1000;

  i = r;
  while (i--)
  {
    mlx_pixel_put(vis->mlx, vis->win, x + i, y - r, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x - i, y - r, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x - r, y - i, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x - r, y + i, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x + i, y + r, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x - i, y + r, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x + r, y + i, color << co);
    mlx_pixel_put(vis->mlx, vis->win, x + r, y - i, color << co);
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

void          draw_line(t_vis *vis, int *v1, int *v2)
{
    int       x = v1[0];
    int       y = v1[1];

    while (x != v2[0] || y != v2[1])
    {
      if (x != v2[0])
        x += x > v2[0] ? -1 : 1;
      if (y != v2[1])
        y += y > v2[1] ? -1 : 1;
      mlx_pixel_put(vis->mlx, vis->win, x, y, -100000);
    }
}

void          connect_ver(t_vis *vis)
{
  t_vertix   **ver;
  t_edge      *e;
  int         *v1, *v2;

  e = (t_edge *)*vis->edge;
  while (e)
  {
    v1 = ft_new_array(2, 0);
    v2 = ft_new_array(2, 0);
    v1[0] = (find_ver(vis->ver, e->e1))->x;
    v1[1] = (find_ver(vis->ver, e->e1))->y;
    v2[0] = (find_ver(vis->ver, e->e2))->x;
    v2[1] = (find_ver(vis->ver, e->e2))->y;
    draw_line(vis, v1, v2);
    free(v1);
    free(v2);
    e = e->next;
  }
}

void        draw_start(t_vis *vis)
{
  t_vertix  *v;

  v = (t_vertix *)*vis->ver;
  while (v)
  {
      draw_square(vis, v->x, v->y, 35, v->mod == 1 ?
        16u : v->mod == 2 ? 1u : 8u);
      v = v->next;
  }
  connect_ver(vis);
}

void    draw_ant(t_vis *vis)
{
  t_ants    *a;
  t_vertix  *v;
  int       *s;
  int        *z;

  v = (t_vertix *)*vis->ver;
  vis->img = mlx_xpm_file_to_image(vis->mlx, "skin/rat.xpm", s, z);

  while (v)
  {
    mlx_put_image_to_window(vis->mlx, vis->win, vis->img, v->x, v->y);
    v = v->next;
//   mlx_put_image_to_window(vis->mlx, vis->win, vis->img, v->x, v->y);
  }

}

int     handle_keys(int code, t_vis *vis)
{
    if (code == 120)
    {
      free (vis);
      exit (0);
    }
    else if (code == 122)
      draw_ant(vis);
}

t_vis     *init_mlx(t_ants **ants, t_vertix **ver, t_edge **edge)
{
  t_vis   *vis;

  if (!(vis = ft_memalloc(sizeof(t_vis))))
    put_error(12, 0, NULL);
  vis->mlx = mlx_init();
  vis->win = mlx_new_window(vis->mlx, 800, 600, "prog");
  vis->ants = ants;
  vis->ver = ver;
  vis->edge = edge;
  return (vis);
}
