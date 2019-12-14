#include "lem_in.h"

void			free_ants(t_ants **s)
{
	t_ants			*a;
	t_ants			*next;

	a = *s;
	while (a)
	{
		next = a->next;
		free(a);
		a = next;
	}
	a = NULL;
}

static void		push_back(t_ants **dst, t_ants *ant)
{
	t_ants		*a;

	a = *dst;
	if (!*dst)
		*dst = ant;
	else
	{
		while (a->next)
			a = a->next;
		a->next = ant;
		ant->next = NULL;
	}
}

static t_ants	*init_ant(int id, int pos)
{
	t_ants		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	tmp->id = id;
	tmp->path = -1;
	return (tmp);
}

static int 			ants_per_room(t_ants **ants, int path)
{
	t_ants			*a;
	int 			r;

	r = 0;
	a = *ants;
	while (a)
	{
		if (a->path == path)
			r++;
		a = a->next;
	}
	return (r);
}

t_list				*get_i_paths(t_list **paths, int value)
{
	t_list			*l;

//	if (value == ft_lstlen(paths))
//		return (NULL);
	l = *paths;
	while (l && value--)
		l = l->next;
	return (l);
}

static void			dispatcher(int amount, t_list **paths, t_ants **ants)
{
	int 			p_len;
	int 			p_next_len;
	int 			a;
	int 			i;
	t_list			*tmp;
	t_ants			*an;

	i = 0;
	an = *ants;
	an->path = 0;
	an = an->next;
	amount -= 1;
	while (amount--)
	{
		p_len = path_len((t_path **)&get_i_paths(paths, i)->content);
//		ft_printf("rooms in path [%d]: %d\n", i, p_len);
		a = ants_per_room(ants, i);
//		ft_printf("ants in this room %d\n", a);
		if (!(tmp = get_i_paths(paths, i + 1)))
		{
			i = -1;
			tmp = get_i_paths(paths, i + 1);
		}
		p_next_len = path_len((t_path **)&tmp->content);
//		ft_printf("Rooms in path [%d]: %d\n\n", i, p_next_len);
		an->path = (p_len + a) <= p_next_len ? i : ++i;
		an = an->next;
	}
}

static int 		is_super_way(t_list **paths)
{
	t_list		*l;
	t_path		*p;

	l = *paths;
	while (l)
	{
		p = l->content;
		if (path_len(&p) == 2)
			return (1);
		l = l->next;
	}
	return (0);
}

static void		set_super_flag(t_ants **ants)
{
	t_ants		*a;

	a = *ants;
	while (a)
	{
		a->path = 0;
		a->super_way = 1;
		a = a->next;
	}
}

static void		link_nodes(t_ants **ants, t_list **paths)
{
	t_ants		*a;
	t_list		*tmp;

	a = *ants;
	while (a)
	{
		tmp = get_i_paths(paths, a->path);
		a->pos = get_i_path_node((t_path **)&tmp->content, a->indx);
		a = a->next;
	}
}

t_ants 			*spawn_ants(int amount, t_list **paths)
{
	int 	i;
	int 	tmp;
	t_ants	*node;
	t_ants	*ants = NULL;

	i = 1;
	tmp = amount;
	while (tmp--)
	{
		node = init_ant(0, 0);
		push_back(&ants, node);
		i++;
	}
	if (is_super_way(paths))
		set_super_flag(&ants);
	else
		dispatcher(amount, paths, &ants);
	link_nodes(&ants, paths);
	return (ants);
}
