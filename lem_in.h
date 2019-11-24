#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"


//#2147483647
//#-2147483648

typedef struct		s_mx
{
	int 			**mx;
	int 			size;
}					t_mx;

typedef struct		s_path
{
	int				node;
	int				parent;
	struct 	s_path	*next;
}					t_path;

/*
**	Struct tools
*/

t_path 				*get_shortest_path(t_mx *M);

t_path 				*create_node(int v, int par);
void				push_back(t_path **path, t_path *node);
void				push_front(t_path **dst, t_path *node);
int 				path_len(t_path **dst);
void				add_path_to_lst(t_list **lst, t_path *path);
void				free_path(t_path **s);
void				print_paths(t_list **lst);
void				print_path(t_path **path);
void				free_list(t_list **tab);
int 				is_paths(t_mx *M);

/*
**	Matrix tools
*/

t_mx				*make_mx(int size);
void				print_mx(int **mx, int size);
void				free_mx(t_mx *M);
void				set_to_zero(int **mx, int size);

int					exclude_overlap(int **mx, int size);

int					*init_tab(int size, int c);
void				print_tab(int *tab, int size);

#endif //LEM_IN_LEM_IN_H
