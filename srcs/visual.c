#include <mlx.h>
#include <stdlib.h>
#include "lem_in.h"

void      draw_square(void *mlx, void *win, int x, int y, int r, unsigned co)
{
  int     i;
  int     color = 1000;

  i = r;
  while (i--)
  {
    mlx_pixel_put(mlx, win, x - i, y - r, color << co);
    mlx_pixel_put(mlx, win, x + i, y - r, color << co);
    mlx_pixel_put(mlx, win, x - r, y - i, color << co);
    mlx_pixel_put(mlx, win, x - r, y + i, color << co);
    mlx_pixel_put(mlx, win, x + i, y + r, color << co);
    mlx_pixel_put(mlx, win, x - i, y + r, color << co);
    mlx_pixel_put(mlx, win, x + r, y + i, color << co);
    mlx_pixel_put(mlx, win, x + r, y - i, color << co);
  }
}

void      draw_start(void *mlx, void *win, t_vertix **ver)
{
  int       *a = (int *)malloc(sizeof(int) * 1);
  int       *b = (int *)malloc(sizeof(int) * 1);
  t_vertix  *v;
  void      *pic;

  v = *ver;
  while (v)
  {
      mlx_string_put (mlx, win, v->x - 20, v->y - 20, 100 << 8u, v->name);
      if (v->mod == 1)
      {
        pic = mlx_xpm_file_to_image(mlx, "skin/rat.xpm", a, b);
        mlx_put_image_to_window(mlx, win, pic, v->x - 20, v->y - 10);
      }
      draw_square(mlx, win, v->x, v->y, 35, v->mod == 1 ?
        16u : v->mod == 2 ? 1u : 8u);
      v = v->next;
  }
  free(a);
  free(b);
  return ;
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

void        draw_line(void *mlx, void *win, int *v1, int *v2)
{
    int     x = v1[0];
    int     y = v1[1];

    while (x != v2[0] || y != v2[1])
    {
      if (x != v2[0])
        x += x > v2[0] ? -1 : 1;
      if (y != v2[1])
        y += y > v2[1] ? -1 : 1;
      mlx_pixel_put(mlx, win, x, y, -100000);
    }
}

void        connect_ver(void *mlx, void *win, t_vertix **ver, t_edge **edge)
{
  t_vertix  *v;
  t_edge    *e;
  int       *v1;
  int       *v2;

  e = *edge;
  while (e)
  {
    v1 = ft_new_array(2, 0);
    v2 = ft_new_array(2, 0);
    v1[0] = (find_ver(ver, e->e1))->x;
    v1[1] = (find_ver(ver, e->e1))->y;
    v2[0] = (find_ver(ver, e->e2))->x;
    v2[1] = (find_ver(ver, e->e2))->y;
    draw_line(mlx, win, v1, v2);
    free(v1);
    free(v2);
    e = e->next;
  }
}

int     handle_keys(int code, void *param)
{
//  ft_printf("[%d]\n", code)
    if (code == 120)
      exit(0);
    if (code == 122)
        ft_printf("hey");
}

int        visual(t_vertix **ver, t_edge **edge)
{
  void    *mlx;
  void    *win;
  void    *pic;
  t_vertix *v;
  t_edge   *e;

  mlx = mlx_init();
  win = mlx_new_window(mlx, 800, 600, "prog");
  draw_start(mlx, win, ver);
  connect_ver(mlx, win, ver, edge);

  mlx_key_hook(win, &handle_keys, NULL);
  mlx_loop(mlx);
  return (0);
}
