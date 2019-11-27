#include "lem_in.h"

static int				parse_room_name(const char *line, char **name, int lc)
{
	const char 			*start;
	int 				i;

	i = 0;
	start = line;
	line += skip_spaces(line);
	if (*line == 'L')
		put_error(2, lc);
	while (line[i] && line[i] != ' ')
			i++;
	if (!(*name = ft_strndup(line, i)))
		put_error(12, lc);
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
		put_error(5, lc);
	i = 0;
	while (name[i] && name[i] != '-')
		i++;
	if (!(a = ft_strndup(name, i)))
		put_error(12, 0);
	name += i + 1;
	if (!*name)
		put_error(3, lc);
	if (!(b = ft_strdup(name)))
		put_error(12, 0);
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
				put_error(3, lc);
			line += lem_atoi(line, xy, i++, lc);
		}
		if (xy[0] < 0 || xy[1] < 0)
			put_error(3, lc);
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
			put_error(1, lc);
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
		put_error(0, 0);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		put_error(12, 0);
	while (read(fd, buf, sizeof(buf)) > 0)
		ft_vec_add(&vec, buf);
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		put_error(12, 0);
	}
	return (vec);
}

static int				cut_after_n(const char *src, char **dst, int lc)
{
	int 				i;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (!i)
		put_error(4, lc);
	if (!(*dst = ft_strndup(src, i)))
		put_error(12, 0);
	return (i);
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
	while ((i_total[1]))
	{
		i_total[0] = cut_after_n(store[0], (char **)&store[1], lc) + 1;
		store[0] += i_total[0];
		i_total[1] -= i_total[0];
		if ((mod_fl[0] = validator(store[1], lc++, mod_fl[0], ptrs)))
			mod_fl[1] |= check_few_mod(mod_fl[0], mod_fl[1], lc);
		ft_strdel((char **)&store[1]);
	}
	check_no_room_given(mod_fl[1], lc);
	ft_vec_del(&buf);
}

/*
void 					reader(int fd, void **ptrs)
{
	static unsigned 	mod = 0;
	unsigned			m_flag;
	int 				lc;
	char 				*line;

	m_flag = 0;
	lc = 1;
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!*line)
			put_error(4, lc);
		if ((mod = validator(line, lc++, mod, ptrs)))
			m_flag |= check_several_modifiers(mod, m_flag, lc);
		ft_strdel(&line);
	}
	check_no_room_given(m_flag, lc);
}
*/