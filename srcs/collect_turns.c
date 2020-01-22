#include "lem_in.h"

static int 			total_actions(t_list *set)
{
	t_path			*r;
	int 			tmp;

	tmp = 0;
	while (set)
	{
		r = set->content;
		tmp += path_len(r) - 1;
		set = set->next;
	}
	return (tmp);
}

int 				calculate_actions(t_list *set, int amount)
{
	int 			tmp;
	int 			len;

	len = ft_lstlen(&set);
	tmp = total_actions(set);
	tmp += amount;
	if (len != 0)
	{
		if (tmp % len)
			tmp--;
		tmp = tmp / len;
	}
	return (tmp);
}

static void 		turn_off(t_edge **edge, t_path *r)
{
	t_edge			*e;

	while (r->next_p)
	{
		e = find_edge(edge, r->curr_v->name, r->next_p->curr_v->name);
		e->on = 0;
		r = r->next_p;
	}
}

t_list 				*collect_turns(t_edge *edge, t_vertex *ver, t_list *xset,
									int *sf)
{
	t_path			*route;
	t_list 			*bset;

	bset = NULL;
	put_paths_on_map(&edge, xset);
	while ((route = breadth_first_search(&edge, &ver, sf[0], sf[1])))
	{
		turn_off(&edge, route);
		add_path_to_lst(&bset, route);
	}
	return (bset);
}
