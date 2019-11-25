#include "lem_in.h"

void		put_error(int type, int lc)
{
	if (type == 0)
		ft_printf("Can't open file\n");
	if (lc > 0)
		ft_printf("%d: {red}error: {eoc}", lc);
	if (type == 1)
		ft_printf("bad modifier\n");
	if (type == 2)
		ft_printf("bad name\n");
	if (type == 3)
		ft_printf("room or link not well formatted\n");
	exit (type);
}

static int		lem_atoi(const char *str, int *num, int pos, int lc)
{
	int			sign;
	long		res;
	int			i;

	i = 0;
	res = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++i)
		sign = *str++ == '-' ? -1 : 1;
	while (*str && ft_isdigit(*str) && ++i)
	{
		if (!*str || *str < '0' || *str > '9')
			put_error(3, lc);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error(3, lc);
	}
	num[pos] = (int)res * sign;
	return (i);
}

unsigned		proceed_sharp(const char *line, int lc)
{
	if (*line++ == '#')
	{
		if (*line == '#')
		{
			line++;
			if (ft_strequ(line, "start"))
				return (1u);
			else if (ft_strequ(line, "end"))
				return (2u);
			else
				put_error(1, lc);
		}
		else
			ft_printf("{yellow}C: %s{eoc}\n", line);
	}
	return (0);
}

int 		parse_room_name(const char *line, char **name, int lc)
{
	const char 	*start;
	int 				i;

	i = 0;
	start = line;
	line += skip_spaces(line);
	if (*line == 'L')
		put_error(2, lc);
	while (line[i] && line[i] != ' ')
			i++;
	*name = ft_strndup(line, i);
	line += i;
	line += skip_spaces(line);
	return (line - start);
}



int			proceed_link_room(const char *line, unsigned mod, int lc)
{
	char 	*name;
	int 	xy[2];
	int 	i = 0;

	xy[0] = -1;
	xy[1] = -1;
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
		mod == 1 ? ft_printf("NAME: {green}[%s] {eoc}", name) :
			mod == 2 ? ft_printf("NAME: {red}[%s] {eoc}", name) :
					ft_printf("NAME: [%s] ", name);
		ft_printf("X: [%d], Y: [%d]\n", xy[0], xy[1]);
		return (mod);
	}
	else
	{
		ft_printf("Link name is [%s]\n", name);
		exit (0);
	}
}

void				parser(const char *line, int lc)
{
	static unsigned mod;

	line += skip_spaces(line);
	if (*line == '#')
	{
		if (mod)
			put_error(1, lc);
		mod = proceed_sharp(line, lc);
		return ;
	}
	proceed_link_room(line, mod, lc);
	mod = 0;
}

int 		main(int ac, char **av)
{
	int 	fd;
	int 	lc;
	int  	ret;
	char 	*line;

	lc = 1;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		put_error(0, 0);
	while ((get_next_line(fd, &line)) > 0)
	{
		parser(line, lc++);
		ft_strdel(&line);
	}
	close(fd);
	return (0);
}
