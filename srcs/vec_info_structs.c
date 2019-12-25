#include "lem_in.h"

int 				pop_lst(t_list **queue)
{
	int 			tmp;
	t_list			*q;
	t_list			*next;

	q = *queue;
	tmp = *((int *)q->content);
	next = q->next;
	free(q);
	*queue = next;
	return (tmp);
}

t_info					*init_info(char *path, unsigned flags)
{
	t_info				*i;

	if (!(i = ft_memalloc(sizeof(t_info))))
	{
		put_error("cannot allocate memory", 0);
		return (NULL);
	}
	i->mod = 0;
	i->flag = 0;
	i->lc = 1;
	i->fd = 0;
	if (flags & OPEN)
		i->fd = open(path, O_RDONLY);
	else
		i->fd = 0;
	i->skip_comments = 0;
	return (i);
}

t_vec					*vec_read(int fd)
{
	t_vec				*vec;
	char 				buf[1];

	if (fd < 0 || read(fd, NULL, 0) < 0)
		put_error("cannot open file", 0);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		put_error("cannot allocate memory", 0);
	while (read(fd, buf, sizeof(buf)) > 0)
	{
		if (vec->total >= 4194304)
		{
			ft_vec_del(&vec);
			put_error("file is too big", 0);
		}
		ft_vec_add(&vec, buf);
	}
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		put_error("cannot allocate memory", 0);
	}
	return (vec);
}