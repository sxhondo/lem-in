/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_route_mgmt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:11:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:11:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 					cross_paths(t_path *fn, t_list **ways)
{
	t_list 				*l;
	t_path 				*tmp;

	while (fn)
	{
		l = *ways;
		while (l)
		{
			tmp = l->content;
			while (tmp)
			{
				if (ft_strequ(fn->curr_v->name, tmp->curr_v->name)
						&& fn->curr_v->mod == 0)
					return (1);
				tmp = tmp->next_p;
			}
			l = l->next;
		}
		fn = fn->next_p;
	}
	return (0);
}