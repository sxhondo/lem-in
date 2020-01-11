/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:39:51 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/22 17:39:52 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static unsigned			get_command(const char *line, t_info *inf)
{
	if (*line++ == '#')
	{
		if (*line == '#')
		{
			if (inf->mod)
				put_error("cannot modify modifier", inf->lc);
			line++;
			line += skip_spaces(line);
			if (ft_strequ(line, "start"))
				return (START);
			else if (ft_strequ(line, "end"))
				return (END);
			else
				put_error("unkown modifier", inf->lc);
		}
	}
	return (inf->mod);
}

static void				proceed_rooms(t_structs *structs, t_info *inf,
															const char *line)
{
	int					i;
	int					*xy;

	i = 0;
	inf->name = NULL;
	xy = ft_new_array(2, -1);
	line += parse_room_name(line, &inf->name, inf->lc);
	if (*line)
	{
		while (*line)
		{
			line += skip_spaces(line);
			if (!*line)
				break ;
			if (*line && i >= 2)
				put_error("room not well formatted", inf->lc);
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

static void				validator(t_structs *structs, t_info *inf,
		const char *line)
{
	line += skip_spaces(line);
	if (*line == '#')
	{
		inf->mod = get_command(line, inf);
		inf->skip_comments++;
		return ;
	}
	if (inf->lc - inf->skip_comments == 1)
	{
		if (!(only_digits(line)))
			put_error("ant-number not well formatted",
					inf->lc - inf->skip_comments);
		structs->ants_amount = check_ants_num(line, inf->lc);
		return ;
	}
	else if (!*line)
		put_error("empty line", inf->lc);
	else
	{
		inf->flag |= check_few_rooms(inf->flag, inf->mod, inf->lc);
		proceed_rooms(structs, inf, line);
		inf->mod = 0;
		return ;
	}
}

void					reader(t_structs *structs, unsigned flags, char *path)
{
	t_info				*inf;
	t_vec				*vec;
	char				*file;
	char				*line;
	int					i;

	inf = init_info(path, flags);
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
	if (!(flags & NO_FILE))
		write(1, vec->data, vec->total - 1);
	write(1, "\n", 1);
	ft_vec_del(&vec);
	free(inf);
}
