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

static unsigned			proceed_rooms(const char *line, void **ptrs, t_info *inf)
{
	char 				*name;
	int 				*xy;
	int 				i;

	i = 0;
	xy = ft_new_array(2, -1);
	line += parse_room_name(line, &name, inf->lc);
	if (*line)
	{
		while (*line)
		{
			line += skip_spaces(line);
			if (*line && i >= 2)
				put_error(3, inf->lc, NULL);
			line += lem_atoi(line, xy, i++, inf->lc);
		}
		if (xy[0] < 0 || xy[1] < 0)
			put_error(3, inf->lc, NULL);
		vertix_push_back((t_vertix **)&ptrs[1], vertix_init(inf->mod, name, xy), inf->lc);
	}
	else
		edge_push_back((t_edge **)&ptrs[2], proceed_links(inf->mod, name, inf->lc),
				(t_vertix **)&ptrs[1], inf->lc);
	ft_strdel(&name);
	free(xy);
	return 0;
}

static unsigned			get_command(const char *line, int lc)
{
	if (*line++ == '#')
	{
		if (*line == '#')
		{
			line++;
			if (ft_strequ(line, "start"))
				return (START);
			else if (ft_strequ(line, "end"))
				return (END);
			else
				put_error(1, lc, NULL);
		}
		else
		{
			ft_printf("{yellow}C: %s{eoc}\n", line);
			return (COMMENT);
		}
	}
	return (0);
}

static void					check_no_room_given(unsigned flag, int lc)
{
	if (!flag)
		put_error(8, lc, NULL);
	if (!(flag & 1u) && (flag & 2u))
		put_error(9, lc, NULL);
	if (flag & 1u && !(flag & 2u))
		put_error(10, lc, NULL);
}

unsigned 				check_few_rooms(unsigned flag, unsigned mod, int lc)
{
	if (flag & mod)
	{
		flag == 1 ? put_error(6, lc, NULL) : put_error(7, lc, NULL);
	}
	return (mod);
}

static void				validator(const char *line, void **structures, t_info *inf)
{
	line += skip_spaces(line);
	if (inf->lc == 1)
	{
		structures[0] = (void *)check_ants_num(line, inf->lc);
		return ;
	}
	else if (*line == '#')
	{
		inf->mod = get_command(line, inf->lc);
		return ;
	}
	else
	{
		inf->flag |= check_few_rooms(inf->flag, inf->mod, inf->lc);
		proceed_rooms(line, structures, inf);
		inf->mod = 0;
		return ;
	}
}

void 					reader(void **ptrs, t_info *inf)
{
	int 				i;
	char 				*file;
	char 				*name;
	t_vec				*vec;

	name = NULL;
	vec = vec_read(inf->fd);
	file = vec->data;
	inf->total = vec->total;
	while (inf->total > 1)
	{
		i = cut_after_symbol(file, &name, '\n', inf->lc) + 1;
		file += i;
		inf->total -= i;
		validator(name, ptrs, inf);
		ft_strdel(&name);
		inf->lc++;
	}
	check_no_room_given(inf->flag, inf->lc);
	ft_printf("%s\n\n", vec->data);
	ft_vec_del(&vec);
	free(inf);
}