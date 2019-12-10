#include "lem_in.h"

static t_vertex			*iter_to_last(t_vertex **ver)
{
	t_vertex			*ptr;

	ptr = *ver;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void					put_to_end(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*last;
	t_vertex			*prev;
	t_vertex			*next;

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

void					put_to_begin(t_vertex **ver)
{
	t_vertex			*p;
	t_vertex			*prev;
	t_vertex			*next;

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

int						cut_after_symbol(const char *src, char **dst, char sym)
{
	int 				i;

	i = 0;
	while (src[i] && src[i] != sym)
		i++;
	if (!(*dst = ft_strndup(src, i)))
	{
		ft_strdel(dst);
		return (0);
	}
	return (i);
}

