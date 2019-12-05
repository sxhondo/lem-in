#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"
#include <mlx.h>

typedef struct 		s_steps
{
	int 			*ids;
	struct s_steps	*next;
}					t_steps;

typedef struct 		s_vis
{
	void 						*mlx;
	void 						*win;
	void						*data;
	int 						bpp;
	int 						sl;
	int 						en;
	void 						*back;
	void 						*skin;
	int 						skin_w;
	int 						skin_h;
	struct s_steps				**steps;
	struct s_vertix 			**ver;
	struct s_edge 				**edge;
	int 						amount;
}									t_vis;

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


/*
**	mover.c
*/
t_steps					*mover(int ants, t_list **paths, t_vertix **ver, t_edge **edge);

/*
**	parser.c
*/
void 					**parser(char *path);
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
**	reader.c
*/
void 					reader(int fd, void **ptrs);

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
int						lst_len(void **lst, unsigned mod);
void					check_no_room_given(unsigned m_flag, int lc);
unsigned				check_sharp(const char *line, int lc);
size_t					check_ants_num(const char *line, int lc);
void					**new_ptr_array(int size);

/*
**	s_ants.c
*/

t_ants 				*spawn_ants(int amount);
void					free_ants(t_ants **s);
void					print_ants(t_ants **s, t_vertix **ver, t_steps **steps, int last, int amounts);

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
t_vertix 			*get_ver(t_vertix **ver, int val);
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

/*
** s_vis.c
*/
t_vertix    *find_ver(t_vertix **ver, char *name);
void     		draw_square(t_vis *vis, int x, int y, int r, unsigned co);
int     		handle_keys(int code, t_vis *vis);


/*
** s_eps.c
*/

void		fill_steps(t_steps **dst, t_ants **ants, int amount);
void		print_steps(t_steps **steps, int amount);
void		steps_free(t_steps **steps);

void 		display_steps(t_steps **steps, t_vertix **ver, t_edge **edge, int amount);


t_vis   	*init_mlx(t_vertix **ver, t_edge **edge, t_steps **steps, int amount);

#endif //LEM_IN_LEM_IN_H
