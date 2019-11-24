#include "lem_in.h"

void		put_error(int type)
{
	if (type == 0)
		ft_printf("{red}Can't open file{eoc}\n");
	if (type == 1)
		ft_printf("{red}bad modifier{eoc}\n");
	if (type == 2)
		ft_printf("{red}bad name{eoc}\n");
	if (type == 3)
		ft_printf("{red}coordinates not well formatted{eoc}\n");
	exit (type);
}

static int		lem_atoi(const char *str, int *num, int pos)
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
			put_error(3);
		res = res * 10 + (*str++ - '0');
		if ((sign == 1 && res > INT32_MAX)
			|| (sign == -1 && res - 2 >= INT32_MAX))
			put_error(3);
	}
	while (*str && *str++ == ' ')
		i++;
	num[pos] = (int)res * sign;
	return (i);
}

unsigned		proceed_sharp(const char *line)
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
				put_error(1);
		}
		else
			ft_printf("{yellow}C: %s{eoc}\n", line);
	}
	return (0);
}

int 		get_name(const char *line, char **name)
{
	int 	i;

	i = 0;
	while (*line == ' ')
		line++;
	while (line[i] != ' ' && line[i])
		i++;
	*name = ft_strndup(line, i);
	line += i;
	while (*line++ == ' ' && *line)
		i++;
	return (i);
}

int			proceed_room(const char *line, unsigned mod)
{
	char 	*name;
	int 	xy[2];
	int 	i = 0;

	if (*line == 'L')
		put_error(2);
	line += get_name(line, &name);
	while (*line)
	{
		if (i >= 2)
			put_error(3);
		line += lem_atoi(line, xy, i++);
	}

	mod == 1 ? ft_printf("NAME: {green}[%s] {eoc}", name) :
		mod == 2 ? ft_printf("NAME: {red}[%s] {eoc}", name) :
			ft_printf("NAME: [%s] ", name);
	ft_printf("X: [%d], Y: [%d]\n", xy[0], xy[1]);
	ft_strdel(&name);
	return (0);
}

void				parser(const char *line)
{
	static unsigned mod;

	if (*line == '#')
	{
		if (mod)
			put_error(1);
		mod = proceed_sharp(line);
		return ;
	}
	mod = proceed_room(line, mod);
}

int 		main(int ac, char **av)
{
	int 	fd;
	char 	*line;

	if ((fd = open("/Users/sxhondo/lem-in/maps/map1", O_RDONLY)) == -1)
		put_error(0);
	while ((get_next_line(fd, &line)) > 0)
	{
		parser(line);
		free (line);
	}
	return (0);
}