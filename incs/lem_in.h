/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:40:23 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 14:49:44 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"

# define START			1u
# define END			2u
# define DIV			4u
# define IN				8u
# define OUT			16u

# define P_DEBUG		1u
# define P_OPEN			2u
# define P_NO_FILE		4u
# define P_NO_OUT		8u
# define P_NEW_LINE		16u

typedef struct			s_info
{
	char				*name;
	unsigned			mod;
	unsigned			flag;
	int					lc;
	int					fd;
	int					total;
	int					skip_comments;
}						t_info;

typedef struct			s_ants
{
	int					id;
	int					path;
	struct s_ants		*next;
	struct s_path		*pos;
}						t_ants;

typedef struct			s_vertex
{
	char				*name;
	unsigned			mod;
	struct s_vertex		*next;
	int					i;
	int					on;
	int					x;
	int					y;
}						t_vertex;

typedef struct			s_arrays
{
	int					*trace;
	int					*inq;
	int					len;
}						t_arrays;

typedef struct			s_edge
{
	char				*tmp_name1;
	char				*tmp_name2;
	t_vertex			*v1;
	t_vertex			*v2;
	int					on;
	unsigned			del;
	int					cost;
	struct s_edge		*next;
}						t_edge;

typedef struct			s_path
{
	t_vertex			*curr_v;
	struct s_path		*next_p;
	struct s_path		*prev_p;
}						t_path;

typedef struct			s_structs
{
	int					ants_amount;
	t_edge				*ce;
	t_vertex			*cv;
	t_edge				*edge;
	t_vertex			*ver;
	t_list				*x_set;
	t_list				*a_set;
	t_list				*b_set;
	t_list				*ways;
	t_ants				*ants;
}						t_structs;


void					reader(t_structs *structs, unsigned flags, char *path);


void					re_route_edges(t_edge **edge, t_vertex *ver);
void					flip_divide(t_path **r, t_edge **e, t_vertex **v);
int						vertex_len(t_vertex **ver);
void					vertex_add(t_structs *s, t_info *inf, int x, int y);
t_vertex				*find_ver_by_name(t_vertex **ver, char *name);
t_vertex				*find_ver_by_index(t_vertex *ver, int i);
void					vertex_free(t_vertex **ver);
t_edge					*find_edge(t_edge **edge, char *v1, char *v2);
void					edge_add(t_structs *structs, t_info *inf);
t_vec					*vec_read(int fd);
t_info					*init_info(char *path, unsigned flags);
int						pop_lst(t_list **queue);
int						cut_after_symbol(const char *src, char **dst, char sym);
int						lem_atoi(const char *str, int *num, int pos, int lc);
int						skip_spaces(const char *str);
unsigned				parse_arguments(int ac, char **arg);
void					turn_edges_off(t_edge *e);
int						parse_room_name(const char *line, char **name, int lc);
int						only_digits(const char *str);
unsigned				check_few_rooms(unsigned flag, unsigned mod, int lc);
void					check_no_room_given(unsigned flag, int lc);
int						check_ants_num(const char *line, int lc);
int						mini_atoi(const char *str);
void					parse_lists(t_structs *structs);
void					put_error(char *err, int lc);
void					link_edges_to_vertex(t_vertex **ver, t_edge *e);
void					edge_print(t_edge *e);
void					vertex_print(t_vertex *ver);
void					ants_print(t_ants **ants);
void					path_print(t_path **path, char mode);
void					ways_print(t_list **ways);
void					print_all(t_structs *str);
void					print_queue(t_list *lst, void **ver);
t_path					*path_init(t_vertex *curr);
void					path_push_back(t_path **dst, t_path *elem);
void					path_push(t_path **dst, t_path *elem);
int						path_len(t_path *dst);
int						compare_sets(t_structs *s);
int						calculate_actions(t_list *set, int amount);
t_list					*collect_turns(t_edge *edge, t_vertex *v, t_list *xset,
						int *sf);
t_path					*get_i_path(t_list *ways, int i);
t_path					*get_i_path_node(t_path **path, int value);
void					vertex_push_back(t_vertex **dst, t_vertex *elem);
void					vertex_push(t_vertex **dst, t_vertex *elem);
void					path_push_init(t_path **d, t_vertex *v1, t_vertex *v2);
void					update_indexes(t_vertex *ver);
t_edge					*edge_init(char *e1, char *e2);
void					edge_push_back(t_edge **dst, t_edge *elem);
void					path_free(t_path **s);
void					edge_free(t_edge **edge);
void					ants_free(t_ants **s);
t_vertex				*vertex_duplic(t_vertex **ver, t_vertex *v);
void					vertex_new(t_vertex **ver, char *name, unsigned div);
int						get_index_of_ver(void **vp, t_vertex *v, int len);
void					add_path_to_lst(t_list **lst, t_path *path);
t_list					*solver(t_structs *s);
t_path					*breadth_first_search(t_edge **edge, t_vertex **ver,
				int s, int f);
t_path					*trace_route(t_vertex **ver, int *trace, int s, int f);
void					mover(t_ants *ants, unsigned flag);
t_ants					*spawn_ants(int amount, t_list *ways);
t_list					*get_i_paths(t_list **paths, int value);
int						ants_per_path(t_ants *ants, int path);
void					ants_push_back(t_ants **dst, t_ants *ant);
t_ants					*ant_init();
t_list					*duplicate_set(t_list *s);
t_list					*add_shortest_paths(t_list **ways, t_edge **e,
													void **ver, int len);
void					free_list(t_list **tab);
void					set_indexes_of_ver(t_edge **edge, void **ver, int len);
void					vertex_dupl(t_vertex **ver, char *name, unsigned div);
int						*find_sd(t_vertex *ver);
void					count_print_nl(t_vec *vec);

#endif
