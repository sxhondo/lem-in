#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"

typedef struct		s_vertix
{
	char 			*name;
	unsigned 		mod;
	int 			x;
	int 			y;
	struct s_vertix *next;
}					t_vertix;

typedef struct		s_edge
{
	char 			*e1;
	char 			*e2;
	struct s_edge 	*next;
}					t_edge;

typedef struct		s_path
{
	int				node;
	int				parent;
	struct 	s_path	*next;
}					t_path;

typedef struct		s_mx
{
	int 			**mx;
	int 			size;
}					t_mx;

/*
**	parser.c
*/
void 					**parser(char *path);

/*
**	solver.c
*/

int 					solver(t_mx *M, t_vertix **ver);
t_path 					*get_shortest_path(t_mx *M);

/*
**	structurise_list.c
*/
void					put_to_start(t_vertix **ver);
void					put_to_end(t_vertix **ver);

/*
**	reader.c
*/
void 					reader(int fd, void **ptrs);

/*
**	validating_tools.c
*/
void					put_error(int type, int lc, void **free);
int 					skip_spaces(const char *str);
int						lem_atoi(const char *str, int *num, int pos, int lc);
unsigned				check_few_mod(unsigned mod, unsigned m_flag, int lc);
int						lst_len(void **lst, unsigned mod);
void					check_no_room_given(unsigned m_flag, int lc);
unsigned				check_sharp(const char *line, int lc);
size_t					check_ants_num(const char *line, int lc);

/*
**	struct_edge.c
*/

void					edge_free(t_edge **edge);
void					edge_print(t_edge **edge);
t_edge					*edge_init(char *e1, char *e2);
void					edge_push_back(t_edge **edge, t_edge *elem,
											t_vertix **ver, int lc);


/*
**	struct_vertix.c
*/

void					vertix_free(t_vertix **ver);
void					vertix_print(t_vertix **ver);
t_vertix				*vertix_init(unsigned mod, char *name, const int *xy);
void					vertix_push_back(t_vertix **ver, t_vertix *elem, int lc);
char 					*get_i_ver(t_vertix **ver, int i);
/*
**	struct_path.c
*/

t_path 				*create_node(int v, int par);
void				push_back(t_path **path, t_path *node);
void				push_front(t_path **dst, t_path *node);
int 				path_len(t_path **dst);
void				add_path_to_lst(t_list **lst, t_path *path);
void				free_path(t_path **s);
void				print_paths(t_list **lst, t_vertix **ver);
void				print_path(t_path **path, t_vertix **ver);
void				free_list(t_list **tab);
int 				is_paths(t_mx *M);

/*
**	Matrix tools
*/

t_mx				*make_mx(int size);
void				print_mx(int **mx, int size, t_vertix **ver);
void				free_mx(t_mx *M);
void				set_to_zero(int **mx, int size);

int					exclude_overlap(int **mx, int size);

int					*init_tab(int size, int c);
void				print_tab(int *tab, int size);

#endif //LEM_IN_LEM_IN_H
