#include "lem_in.h"

t_info					*init_info()
{
	t_info				*i;

	if (!(i = ft_memalloc(sizeof(t_info))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	i->mod = 0;
	i->flag = 0;
	i->lc = 1;
	i->fd = open("maps/pdf", O_RDONLY);
	return (i);
}

/* check_ants_num */

int					mini_atoi(const char *str)
{
	long			res;

	res = 0;
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		if (res > INT32_MAX)
			return (-1);
	}
	return ((int)res);
}

static int					check_ants_num(const char *line, int lc)
{
	int						i;
	int 					ants;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ' ')
			put_error("ants number not well formatted", lc);
		i++;
	}
	ants = mini_atoi(line);
	if (ants < 0)
		put_error("ants number not well formatted", lc);
	if (ants == 0)
		put_error("ants number cannot be 0", lc);
	return (ants);
}

/* *** */

/* read and cut line */

static int 		skip_spaces(const char *str)
{
	int 		i;

	i = 0;
	while (*str && (*str == ' ' || *str == '\t'))
	{
		str++;
		i++;
	}
	return (i);
}

static t_vec			*vec_read(int fd)
{
	t_vec				*vec;
	char 				buf[1];

	if (fd < 0 || read(fd, NULL, 0) < 0)
		put_error("cannot open file", 0);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		put_error("cannot allocate memory", 0);
	while (read(fd, buf, sizeof(buf)) > 0)
	{
		if (vec->total >= 4194304)
		{
			ft_vec_del(&vec);
			put_error("file is too big", 0);
		}
		ft_vec_add(&vec, buf);
	}
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		put_error("cannot allocate memory", 0);
	}
	return (vec);
}

/* *** */

int					lem_atoi(const char *str, int *num, int pos, int lc)
{
	int				sign;
	long			res;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	if (!ft_isdigit(*str))
		put_error("bad modifier", lc);
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			put_error("bad modifier", lc);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error("bad modifier", lc);
	}
	num[pos] = (int)res * sign;
	return (i);
}

static int				parse_room_name(const char *line, char **name, int lc)
{
	const char 			*start;
	int 				i;

	start = line;
	line += skip_spaces(line);
	if (*line == 'L')
		put_error("room name cannot stars with 'L'", lc);
	i = cut_after_symbol(line, name, ' ');
	line += i;
	line += skip_spaces(line);
	return ((int)(line - start));
}

static void					check_no_room_given(unsigned flag, int lc)
{
	if (!flag)
		put_error("start and end rooms are not given", lc);
	if (!(flag & 1u) && (flag & 2u))
		put_error("start room is not given", lc);
	if (flag & 1u && !(flag & 2u))
		put_error("end room is not given", lc);
}

static unsigned			get_command(const char *line, t_info *inf)
{
	if (*line++ == '#')
	{
		if (*line == '#')
		{
			if (inf->mod)
				put_error("cannot modify modifier", inf->lc - 1);
			line++;
			if (ft_strequ(line, "start"))
				return (START);
			else if (ft_strequ(line, "end"))
				return (END);
			else
				put_error("unknown command", inf->lc);
		}
		else
		{
			ft_printf("{yellow}C: %s{eoc}\n", line);
			return (inf->mod);
		}
	}
	return (0);
}

static void				proceed_rooms(t_structs *structs, t_info *inf,
										 const char *line)
{
	int 				i;
	int 				*xy;

	i = 0;
	inf->name = NULL;
	xy = ft_new_array(2, -1);
	line += parse_room_name(line, &inf->name, inf->lc);
	if (*line)
	{
		while (*line)
		{
			line += skip_spaces(line);
			if (*line && i >= 2)
				put_error("!!!", 0);
			line += lem_atoi(line, xy, i++, inf->lc);
		}
		if (xy[0] < 0 || xy[1] < 0)
			put_error("room not well formatted", inf->lc);
		vertex_add(structs, inf, xy[0], xy[1]);
	}
	else
		edge_add(structs, inf);
	free(xy);
}

unsigned 				check_few_rooms(unsigned flag, unsigned mod, int lc)
{
	if (flag & mod)
	{
		flag == 1 ? put_error("several start rooms", lc)
			: put_error("several end rooms", lc);
	}
	return (mod);
}

static void				validator(t_structs *structs, t_info *inf, const char *line)
{
	line += skip_spaces(line);
	if (inf->lc == 1)
	{
		structs->ants_amount = check_ants_num(line, inf->lc);
		return ;
	}
	else if (*line == '#')
	{
		inf->mod = get_command(line, inf);
		return ;
	}
	else
	{
		inf->flag |= check_few_rooms(inf->flag, inf->mod, inf->lc);
		proceed_rooms(structs, inf, line);
		inf->mod = 0;
		return ;
	}
}

void 					reader(t_structs *structs)
{
	t_info				*inf;
	t_vec				*vec;
	char 				*file;
	char 				*line;
	int 				i;

	inf = init_info();
	vec = vec_read(inf->fd);
	file = vec->data;
	inf->total = vec->total;
	while (inf->total > 1)
	{
		i = cut_after_symbol(file, &line, '\n') + 1;
		validator(structs, inf, line);
		file += i;
		inf->total -= i;
		inf->lc++;
		ft_strdel(&line);
		ft_strdel(&inf->name);
	}
	check_no_room_given(inf->flag, inf->lc);
	ft_printf("%s\n\n", vec->data);
	ft_vec_del(&vec);
	free(inf);
}