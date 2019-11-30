#include "lem_in.h"

static t_vertix			*iter_to_last(t_vertix **ver)
{
	t_vertix			*ptr;

	ptr = *ver;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void					put_to_start(t_vertix **ver)
{
	t_vertix			*p;
	t_vertix			*prev;
	t_vertix			*next;

	if ((*ver)->mod == 1)
		return ;
	p = *ver;
	while (p)
	{
		if (p->next->mod == 1)
		{
			prev = p;
			next = p->next->next;
			p->next->next = *ver;
			(*ver) = p->next;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}

void					put_to_end(t_vertix **ver)
{
	t_vertix			*p;
	t_vertix			*last;
	t_vertix			*prev;
	t_vertix			*next;

	last = iter_to_last(ver);
	if (last->mod == 2)
		return ;
	p = *ver;
	while (p)
	{
		if (p->next->mod == 2)
		{
			prev = p;
			next = p->next->next;
			last = iter_to_last(ver);
			last->next = p->next;
			p->next->next = NULL;
			prev->next = next;
			break ;
		}
		p = p->next;
	}
}

int 				line_is_busy(t_list **lst, t_path **path, int last_node)
{
	int 			val;
	t_list			*l;
	t_path			*p;
	t_path			*ptr;

	p = *path;
	while (p)
	{
		val = p->node;
		l = *lst;
		while (l)
		{
			ptr = l->content;
			while (ptr)
			{
				if (ptr->node == val && ptr->node != 0 && ptr->node != last_node)
					return (1);
				ptr = ptr->next;
			}
			l = l->next;
		}
		p = p->next;
	}
	return (0);
}