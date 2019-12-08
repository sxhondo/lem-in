#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"
#include <mlx.h>

typedef struct		s_ants
{
	int 			pos;
	int 			id;
	struct s_ants 	*next;
}					t_ants;

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


typedef struct 		s_vis
{
	void 						*mlx;
	void 						*win;
	char						*data;
	int 						bpp;
	int 						sl;
	int 						en;
	void 						*back;
	int 						width;
	int 						height;
	void 						*skin;
	int 						skin_w;
	int 						skin_h;
	struct s_list				**turns;
	struct s_list				*t_begin;
	struct s_vertix 			**ver;
	struct s_edge 				**edge;
	int 						amount;
}								t_vis;

/*
**	visual_draw_graph.c
*/
void					draw_graph(t_vis *vis);

/*
**	visual.c
*/
int 					key_handle(int code, t_vis *vis);

/*
**	mover.c
*/
t_list 					*mover(int ants, t_list **paths, t_vertix **ver, t_edge **edge);


/*
**	reader.c
*/
void 					reader(int fd, void **ptrs);


/*
**	parser.c
*/
void 					**parser();
int						**allocate_mx(int x, int y);


/*
**	solver.c
*/

t_list 					*solver(t_mx *M, t_vertix **ver);
t_path 					*get_shortest_path(t_mx *M);
t_path					*exclude_shortest(t_path **path, t_mx *M);

/*
**	structurise_list.c
*/
void					put_to_start(t_vertix **ver);
void					put_to_end(t_vertix **ver);
int 					line_is_busy(t_list **lst, t_path **path, int last_node);

/*
**	put_error.c
*/
void					*put_error(int type, int lc, void **free);
void					*put_error1(int type, void **free);

/*
**	validating_tools.c
*/

int 					ft_strequal(const char *s1, const char *s2);
int 					skip_spaces(const char *str);
int						lem_atoi(const char *str, int *num, int pos, int lc);
unsigned				check_few_mod(unsigned mod, unsigned m_flag, int lc);
void					check_no_room_given(unsigned m_flag, int lc);
unsigned				check_sharp(const char *line, int lc);
size_t					check_ants_num(const char *line, int lc);
void					**new_ptr_array(int size);

/*
**	s_ants.c
*/

t_ants 					*spawn_ants(int amount);
void					free_ants(t_ants **s);
void					print_ants(t_ants **s, t_vertix **ver, t_list **turns, int last, int amounts);

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
int 					ver_len(t_vertix **ver);
t_vertix 				*find_ver_by_index(t_vertix **ver, int i);
t_vertix     			*find_ver_by_name(t_vertix **ver, char *name);
void					vertix_free(t_vertix **ver);
void					vertix_print(t_vertix **ver);
t_vertix				*vertix_init(unsigned mod, char *name, const int *xy);
void					vertix_push_back(t_vertix **ver, t_vertix *elem, int lc);



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
**	s_mx.c
*/

t_mx				*make_mx(int size);
void				print_mx(int **mx, int size, t_vertix **ver);
void				free_mx(t_mx *M);
void				set_to_zero(int **mx, int size);
int					exclude_overlap(int **mx, int size);

int					*init_tab(int size, int c);
void				print_tab(int *tab, int size);

#endif //LEM_IN_LEM_IN_H
