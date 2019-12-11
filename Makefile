NAME = lem-in
CC = gcc
#CFLAGS = -Wall -Wextra -Werror


INC_DIR = incs/
LIB_DIR = libft/
LIB_FT = libft.a

SRCS_DIR = srcs/
SRCS_LIST=\
		main.c\
		mover.c\
		solver.c\
		reader.c\
		put_error.c\
		tools.c\
		s_vertex.c\
		s_ants.c\
		s_edge.c\
		s_path.c\
		s_mx.c

OBJ_DIR = obj/
OBJ_LIST = $(SRCS_LIST:%.c=%.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(LIB_FT) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L $(LIB_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
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
