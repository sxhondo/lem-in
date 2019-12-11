#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft.h"
#include "ft_printf.h"
#include <mlx.h>

# define START		1u
# define END		2u
# define COMMENT	3u

typedef struct		s_ants
{
	int 			pos;
	int 			id;
	struct s_ants 	*next;
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
	char 			*v1;
	char 			*v2;
	struct s_edge 	*next;
}					t_edge;

typedef struct		s_path
{
	int				node;
	int				parent;
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
**	put_error.c
*/
void					put_error(char *err, int lc);

/*
**	reader.c
*/
void 					reader(t_structs *structs);

/*
**	s_vertex.c
*/
int 					vertex_len(t_vertex **ver);
void					vertex_add(t_structs *structs, t_info *inf, int x, int y);
int						get_i_by_name(t_vertex **ver, char *name);
t_vertex     			*find_ver_by_name(t_vertex **ver, char *name);
t_vertex 				*find_ver_by_index(t_vertex **ver, int i);
void					vertex_print(t_vertex **ver);
void					vertex_free(t_vertex **ver);

/*
**	s_edge.c
*/
void 					edge_add(t_structs *structs, t_info *inf);
void					edge_print(t_edge **edge);
void					edge_free(t_edge **edge);


/*
**	tools.c
*/
void					put_to_begin(t_vertex **ver);
void					put_to_end(t_vertex **ver);
int						cut_after_symbol(const char *src, char **dst, char sym);
/*
**	s_mx.c
*/
void 					create_matrix(t_structs *structs);
void					print_mx(int **mx, int size, t_vertex **ver);
int						exclude_overlap(int **mx, int size);

/*
**	s_path.c
*/
void					path_print(t_path **path, t_vertex **ver);
void					paths_print(t_list **lst, t_vertex **ver);
t_path 					*path_create_node(int v, int par);
void					path_push_back(t_path **path, t_path *node);
void					path_push_front(t_path **dst, t_path *node);
void					path_free(t_path **s);
int 					path_len(t_path **dst);
void					add_path_to_lst(t_list **lst, t_path *path);
int 					is_paths(int **mx, int m_size);
int 					line_is_busy(t_list **lst, t_path **path, int last_node);
void					list_free(t_list **tab);
int 					get_last_node(t_list **paths);

/*
**	solver.c
*/
t_list 					*solver(int **mx, int m, t_vertex **ver);
t_path 					*get_shortest_path(int **mx, int m_size);

/*
**	mover.c
*/
t_ants 					*mover(int amount, t_vertex **ver, t_list **paths);

/*
**	s_ants.c
*/
t_ants 					*spawn_ants(int amount);
void					free_ants(t_ants **s);


#endif //LEM_IN_LEM_IN_H
