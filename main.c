#include "lem_in.h"

unsigned			proceed_sharp(const char *line, int lc)
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

int 				parse_room_name(const char *line, char **name, int lc)
{
	const char 		*start;
	int 			i;

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
	return ((int)(line - start));
}

void				proceed_links(unsigned mod, char *name, int lc)
{
	if (mod)
		put_error(5, lc);
	ft_printf("LINK: [%s]\n", name);
}

unsigned			proceed_rooms(const char *line, unsigned mod, int lc)
{
	char 			*name;
	int 			xy[2];
	int 			i;

	i = 0;
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
		verbose_collecting_data(mod, name, xy[0], xy[1]);
	}
	else
		proceed_links(mod, name, lc);
	ft_strdel(&name);
	return (0);
}

unsigned	parser(const char *line, int lc, unsigned mod)
{
	line += skip_spaces(line);
	if (*line == '#')
	{
		if (mod)
			put_error(1, lc);
		return (proceed_sharp(line, lc));
	}
	proceed_rooms(line, mod, lc);
	return (0);
}

unsigned		check_several_modifiers(unsigned mod, unsigned m_flag, int lc)
{
	if (mod == 1)
	{
		if ((m_flag & 1u))
			put_error(6, lc);
		return (1u);
	}
	else if (mod == 2)
	{
		if ((m_flag & 2u))
			put_error(7, lc);
		return (2u);
	}
	else
		put_error(7, lc);
	return (0);
}

void				check_no_room_given(unsigned m_flag, int lc)
{
	if (!m_flag)
		put_error(8, lc);
	if (!(m_flag & 1u) && (m_flag & 2u))
		put_error(9, lc);
	if (m_flag & 1u && !(m_flag & 2u))
		put_error(10, lc);
}

int 				main(int ac, char **av)
{
	static unsigned mod = 0;
	unsigned		m_flag;
	int 			fd;
	int 			lc;
	char 			*line;

	m_flag = 0;
	lc = 1;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		put_error(0, 0);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!*line)
			put_error(4, lc);
		if ((mod = parser(line, lc++, mod)))
			m_flag |= check_several_modifiers(mod, m_flag, lc);
		ft_strdel(&line);
	}
	check_no_room_given(m_flag, lc);
	close(fd);
	return (0);
}
