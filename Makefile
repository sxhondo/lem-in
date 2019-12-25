NAME = lem-in
CC = gcc
#CFLAGS = -Wall -Wextra -Werror


INC_DIR = incs/
INC  = $(INC_DIR)lem_in.h

LIB_DIR = libft/
LIB_FT = $(LIB_DIR)libft.a

# 		alg_solver.c\

SRCS_DIR = srcs/
SRCS_LIST= alg_bellman_ford.c alg_bfs.c alg_mover.c alg_route_mgmt.c\
			alg_solver.c alg_tools.c structs_tools.c\
			ants_dispatcher.c ants_struct.c\
			edge_struct.c path_struct.c vertex_struct.c free_structs.c\
			set_vertex_in_position.c validator_tools.c vec_info_structs.c\
			parse_lists.c parse_reader.c parse_tools.c\
			display_info.c main.c

OBJ_DIR = obj/
OBJ_LIST = $(SRCS_LIST:%.c=%.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(NAME)

$(NAME):  $(LIB_FT) $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L $(LIB_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC)
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_FT): $(LIB_DIR)
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
