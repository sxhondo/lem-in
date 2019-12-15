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

//typedef struct		s_edge
//{
//	char 			*v1;
//	char 			*v2;
//	struct s_edge 	*next;
//}					t_edge;

typedef struct		s_edge
{
	char 			*v1_name;
	char 			*v2_name;
	t_vertex		*v1;
	t_vertex 		*v2;
	int 			cost;
	struct s_edge 	*next;
}					t_edge;

typedef struct		s_path
{
	t_vertex		*curr;
	t_vertex		*prev;
//	int				node;
//	int				parent;
	struct 	s_path	*next;
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
	t_ants			*ants;
	t_list			*paths;
	int 			**mx;
	int 			m_size;
}					t_structs;

/*
**	reader.c
*/
void 					reader(t_structs *structs, unsigned  flags, char *path);

/*
**	s_vertex.c
*/
int 					vertex_len(t_vertex **ver);
void					vertex_add(t_structs *structs, t_info *inf, int x, int y);
int						get_i_by_name(t_vertex **ver, char *name);
t_vertex     			*find_ver_by_name(t_vertex **ver, char *name);
t_vertex 				*find_ver_by_index(t_vertex **ver, int i);
void					vertex_free(t_vertex **ver);

/*
**	s_edge.c
*/
t_edge					*find_edge(t_edge **edge, char *v1, char *v2);
t_vertex				*find_start(t_edge **edge);
void 					edge_add(t_structs *structs, t_info *inf);
void					edge_free(t_edge **edge);
int 					edge_len(t_edge **edge);

/*
**	parsing_lists.c
*/
void 					parse_lists(t_vertex **ver, t_edge **edge);

/*
**	parsing_tools.c
*/
int						cut_after_symbol(const char *src, char **dst, char sym);
int						lem_atoi(const char *str, int *num, int pos, int lc);
int 					skip_spaces(const char *str);

/*
**	display_info.c
*/
void					put_error(char *err, int lc);
void					edge_print(t_edge **edge);
void					vertex_print(t_vertex **ver);
void					print_mx(int **mx, int size, t_vertex **ver);
void					ants_print(t_ants **ants, t_vertex **ver);
void					path_print(t_path **path, t_vertex **ver);
void					paths_print(t_list **lst, t_vertex **ver);
void					print_all(t_structs *str);

/*
**	s_mx.c
*/
void 					create_matrix(t_structs *structs);
int						exclude_overlap(int **mx, int size);

/*
**	s_path.c
*/
t_path 					*path_init(t_vertex **ver);
void					path_add(t_path **dst, t_vertex *elem, t_vertex *prev);
void					path_push(t_path **dst, t_path *elem);
int 					path_len(t_path **dst);
void					path_free(t_path **s);
t_path 					*path_duplicate(t_path *dupl);
int 					is_paths(t_edge **edge);

//void					path_push_back(t_path **path, t_path *node);
//void					path_push_front(t_path **dst, t_path *node);
//void					path_free(t_path **s);
//int 					path_len(t_path **dst);
//void					add_path_to_lst(t_list **lst, t_path *path);
//int 					is_paths(int **mx, int m_size);
//int 					line_is_busy(t_list **lst, t_path **path, int last_node);
//void					list_free(t_list **tab);
//t_path					*get_i_path_node(t_path **path, int value);

/*
**	solver.c
*/
t_list					*solver(t_edge **edge, t_vertex **ver);

/*
**	bfs.c
*/
t_path					*get_shortest_path(t_edge **edge);

/*
**	mover.c
*/
void					mover(t_vertex **ver, t_ants **ants, unsigned flags);

/*
**	s_ants.c
*/
t_ants 					*spawn_ants(int amount, t_list **paths);
t_list					*get_i_paths(t_list **paths, int value);
void					free_ants(t_ants **s);

void					free_list(t_list **tab);

#endif
