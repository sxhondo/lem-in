#include "lem_in.h"

void 				free_queue(t_list **que)
{
	t_list 			*q;
	t_list 			*next;

	q = *que;
	while (q)
	{
		next = q->next;
		free(q);
		q = next;
	}
}

void		add_path_to_lst(t_list **lst, t_path *path)
{
	t_list	*node;

	if (!(node = ft_lstnew(path, sizeof(t_path))))
		put_error("cannot allocate memory", 0);
	free(path);
	ft_lstpushback(lst, node);
}
