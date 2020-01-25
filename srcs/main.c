/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:31:17 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/23 13:19:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_structs	*init_structs(void)
{
	t_structs		*s;

	if (!(s = ft_memalloc(sizeof(t_structs))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	return (s);
}

int					main(int ac, char **av)
{
	unsigned		flag;
	t_structs		*structs;

	flag = parse_arguments(ac, av);
	structs = init_structs();	
	reader(structs, flag, av[ac - 1]);
	parse_lists(structs);
	
	// structs->ways = solver(structs);
	// structs->ants = spawn_ants(structs->ants_amount, structs->ways);
	// mover(structs->ants, flag);
	// if (flag & DEBUG)
	// 	print_all(structs);
	// free_structs(structs);
	exit(0);
}
