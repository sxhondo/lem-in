#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"

typedef struct		s_path
{
	int 			cost;
	int				node;
	int 			parent;
	struct s_path	*next;
}					t_path;

t_path 				*create_node(int v, int par);
void				push_back(t_path **path, t_path *node);
void				push_front(t_path **dst, t_path *node);

int 				**make_matrix(int size);
int 				**duplicate_matrix(int **mx, int size);
void				set_mx_to(int **mx, int size, int c);
int 				count_max_edges(int **mx, int size);
void				print_matrix(int **mx, int size);
void				free_matrix(int **mx, int size);
void				free_path(t_path **s);
void				set_to_zero(int **mx, int size);
int					find_overlap(int **mx, int size);

void				try_another_path(t_path **s, int i);
int 				path_len(t_path **dst);
void				print_paths(t_path **p1, t_path **p2);
void				free_tab(t_list **tab);
int 				find_marked(t_path **s);

#endif //LEM_IN_LEM_IN_H
