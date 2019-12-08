
NAME = lem-in
CC = gcc
#CFLAGS = -Wall -Wextra -Werror

LDIR = libft/
LINC = $(LDIR)incs
LIBFT = $(LDIR)libft.a
MLXDIR = minilibx/
INC_DIR = incs/
INC = lem_in.h
SRCS_DIR = srcs/
SRCS_LIST=\
		main.c\
		mover.c\
		parser.c\
		solver.c\
		put_error.c\
		reader.c\
		s_ants.c\
		s_edge.c\
		s_mx.c\
		s_path.c\
		s_vertix.c\
		structurise_list.c\
		validating_tools.c\
		visual.c\
		visual_draw_graph.c

OBJ = $(SRCS_LIST:%.c=%.o)

all: $(LIBFT) $(NAME)

# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ) -L $(LDIR) -lft -o $(NAME)\
# 		-L $(LDIR) -lft -I $(MLXDIR) -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L $(LDIR) -lft -o $(NAME)\
		-L $(LDIR) -lft -I $(MLXDIR) -L $(MLXDIR) -lmlx -lXext -lX11 -o $(NAME)


%.o: $(SRCS_DIR)%.c
	$(CC) -c $(CFLAGS) -I./$(LINC) -I ./ $<

$(LIBFT): $(LDIR)
	make -C $(LDIR)
clean:
	@rm -f $(OBJ)
	@make clean -C $(LDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LDIR)

re: fclean all

.PHONY: all clean fclean re
