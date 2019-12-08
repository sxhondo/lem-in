#include "incs/lem_in.h"

static int				cut_after_symbol(const char *src, char **dst, char sym, int lc)
{
	int 				i;

	i = 0;
	while (src[i] && src[i] != sym)
		i++;
	if (!i)
		put_error(4, lc, NULL);
	if (!(*dst = ft_strndup(src, i)))
		put_error(12, 0, NULL);
	return (i);
}

static int				parse_room_name(const char *line, char **name, int lc)
{
	const char 			*start;
	int 				i;

	start = line;
	line += skip_spaces(line);
	if (*line == 'L')
		put_error(2, lc, NULL);
	i = cut_after_symbol(line, name, ' ', lc);
	line += i;
	line += skip_spaces(line);
	return ((int)(line - start));
}

static t_edge			*proceed_links(unsigned mod, char *name, int lc)
{
	int 				i;
	char 				*a;
	char 				*b;
	t_edge				*tmp;

	if (mod)
		put_error(5, lc, NULL);
	i = cut_after_symbol(name, &a, '-', lc);
	name += i;
	if (!*name || !(*name + 1))
		put_error(3, lc, NULL);
	name += 1;
	if (!(b = ft_strdup(name)))
		put_error(12, 0, NULL);
	tmp = edge_init(a, b);
	return (tmp);
}

static unsigned			proceed_rooms(const char *line, unsigned mod, int lc,
															void **ptrs)
{
	char 				*name;
	int 				*xy;
	int 				i;

	i = 0;
	xy = init_tab(2, -1);
	line += parse_room_name(line, &name, lc);
	if (*line)
	{
		while (*line)
		{
			line += skip_spaces(line);
			if (*line && i >= 2)
				put_error(3, lc, NULL);
			line += lem_atoi(line, xy, i++, lc);
		}
		if (xy[0] < 0 || xy[1] < 0)
			put_error(3, lc, NULL);
		vertix_push_back((t_vertix **)&ptrs[1], vertix_init(mod, name, xy), lc);
	}
	else
		edge_push_back((t_edge **)&ptrs[2], proceed_links(mod, name, lc),
				(t_vertix **)&ptrs[1], lc);
	ft_strdel(&name);
	free(xy);
	return 0;
}

static unsigned			validator(const char *line, int lc, unsigned mod,
																void **ptrs)
{
	line += skip_spaces(line);
	if (lc == 1)
		ptrs[0] = (void *)check_ants_num(line, lc);
	else if (*line == '#')
	{
		if (mod)
			put_error(1, lc, NULL);
		return (check_sharp(line, lc));
	}
	else
		proceed_rooms(line, mod, lc, ptrs);
	return (0);
}

static t_vec			*vec_read(int fd)
{
	t_vec				*vec;
	char 				buf[1];

	if (fd < 0 || read(fd, NULL, 0) < 0)
		put_error(0, 0, NULL);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		put_error(12, 0, NULL);
	while (read(fd, buf, sizeof(buf)) > 0)
	{
		if (vec->total >= 4194304)
		{
			ft_vec_del(&vec);
			put_error(-1, 0, NULL);
		}
		ft_vec_add(&vec, buf);
	}
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		put_error(12, 0, NULL);
	}
	return (vec);
}

void 					reader(int fd, void **ptrs)
{
	int 				lc;
	unsigned 			mod_fl[2];
	int  				i_total[2];
	void				*store[2];
	t_vec				*buf;

	lc = 1;
	buf = vec_read(fd);
	mod_fl[0] = 0;
	mod_fl[1] = 0;
	store[0] = buf->data;
	i_total[1] = buf->total;
	while ((i_total[1]) > 1)
	{
		i_total[0] = cut_after_symbol(store[0], (char **)&store[1], '\n', lc) + 1;
		store[0] += i_total[0];
		i_total[1] -= i_total[0];
		if ((mod_fl[0] = validator(store[1], lc++, mod_fl[0], ptrs)))
			mod_fl[1] |= check_few_mod(mod_fl[0], mod_fl[1], lc);
		ft_strdel((char **)&store[1]);
	}
	check_no_room_given(mod_fl[1], lc);
	ft_printf("%s\n\n", buf->data);
	ft_vec_del(&buf);
}