#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"

# define START		1u
# define END		2u

# define DEBUG		1u
# define COLORS		2u
# define OPEN		4u

typedef struct		s_ants
{
	int 			id;
	int 			path;
	struct s_ants 	*next;
	struct s_path 	*pos;
	int 			indx;
	int 			super_way;
}					t_ants;

typedef struct		s_vertex
{
	char 			*name;
	unsigned 		mod;
	int 			x;
	int 			y;
	struct s_vertex *next;
}					t_vertex;

typedef struct		s_edge
{
	char 			*v1_name;
	char 			*v2_name;
	t_vertex		*v1;
	t_vertex 		*v2;
	int 			v1_i;
	int 			v2_i;
	int 			cost;
	int 			bi;
	struct s_edge 	*next;
}					t_edge;

typedef struct		s_path
{
	t_vertex		*curr_v;
	struct 	s_path	*next_p;
	struct 	s_path	*prev_p;
}					t_path;

typedef struct		s_info
{
	char 			*name;
	unsigned 		mod;
	unsigned 		flag;
	int 			lc;
	int 			fd;
	int 			total;
	int 			skip_comments;
}					t_info;

typedef struct 		s_structs
{
	int 			ants_amount;
	t_edge			**edge;
	t_vertex		**ver;
	t_list			*ways;
	t_ants			*ants;
}					t_structs;

/*
**	reader.c
*/
void 					reader(t_structs *structs, unsigned  flags, char *path);

/*
**	vertex_struct.c
*/
int 					vertex_len(t_vertex **ver);
void					vertex_add(t_structs *structs, t_info *inf, int x, int y);
int						get_i_by_name(t_vertex **ver, char *name);
t_vertex     			*find_ver_by_name(t_vertex **ver, char *name);
t_vertex 				*find_ver_by_index(t_vertex **ver, int i);
void					vertex_free(t_vertex **ver);

/*
**	edge_struct.c
*/
t_edge					*find_edge(t_edge **edge, char *v1, char *v2);
t_vertex				*find_start(t_edge **edge);
void 					edge_add(t_structs *structs, t_info *inf);
int 					edge_len(t_edge **edge);

/*
**	parse_lists.c
*/
void 					parse_lists(t_vertex **ver, t_edge **edge);

/*
**	parse_tools.c
*/
int						cut_after_symbol(const char *src, char **dst, char sym);
int						lem_atoi(const char *str, int *num, int pos, int lc);
int 					skip_spaces(const char *str);
unsigned 				parse_arguments(int ac, char **arg);

/*
**	display_info.c
*/
void					put_error(char *err, int lc);
void					edge_print(t_edge **edge);
void					vertex_print(t_vertex **ver);
void					ants_print(t_ants **ants);
void 					path_print(t_path **path, char mode);
void 					ways_print(t_list **ways);
void					print_all(t_structs *str);

/*
**	path_struct.c
*/
t_path 					*path_init(t_vertex *curr);
void 					path_push_back(t_path **dst, t_path *elem);
void					add_path_to_lst(t_list **lst, t_path *path);
void					path_push(t_path **dst, t_path *elem);
int 					path_len(t_path **dst);
t_path					*get_i_path_node(t_path **path, int value);
void					path_push_init(t_path **dst, t_vertex *v1, t_vertex *v2);

/*
**	free_structs.c
*/
void					path_free(t_path **s);
void					edge_free(t_edge **edge);
void					ants_free(t_ants **s);

/*
** alg
*/

/*
**	solver.c
*/
t_list 					*solver(int ants, t_edge **edge, t_vertex **ver);

/*
**	bellman_ford.c
*/
t_path					*get_cheapest_path(t_edge **edge, void **ver, int len);

/*
**	bfs.c
*/
t_path					*breadth_first_search(t_edge **edge,
		void **ver, int len);

/*
**	route_mgmt.c
*/
t_list					*find_overlapping_routes(t_edge **edge,
		t_list **pi, void **vp, int len);

/*
**	tools.c
*/
t_path					*trace_route(void **ver, int *par, int last);
void				    exclude_route(t_path **route, t_edge **edge);
void					swap_ver(t_vertex **v1, t_vertex **v2);

/*
** ants
*/

/*
**	mover.c
*/
void					mover(t_ants **ants, unsigned flags);

/*
**	dispatcher.c
*/
t_ants 					*spawn_ants(int amount, t_list **paths);
t_list					*get_i_paths(t_list **paths, int value);

/*
**	struct.c
*/
int 					ants_per_room(t_ants **ants, int path);
void					ants_push_back(t_ants **dst, t_ants *ant);
t_ants					*ant_init(int id, int pos);

void					free_list(t_list **tab);

#endif
