
NAME = lem-in
CC = gcc
#CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
OBJ_DIR = obj/
LDIR = libft/
LINC = $(LDIR)incs
LIBFT = $(LDIR)libft.a
INC = lem_in.h
SRCS_LIST=\
 			reader.c\
			parser.c\
			solver.c\
			s_edge.c\
			s_path.c\
			s_vertix.c\
			s_mx.c\
			s_ants.c\
			structurise_list.c\
			validating_tools.c\
			put_error.c\
			mover.c\
			visual.c\
			main.c

OBJ_LIST = $(SRCS_LIST:%.c=%.o)

all: $(LIBFT) $(NAME)

# Linux
# $(NAME): $(OBJ_LIST) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ_LIST) -L $(LDIR) -lft -o $(NAME) -I minilibx/ -L minilibx -lmlx -lXext -lX11

# MacOS
$(NAME): $(OBJ_LIST) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_LIST) -L $(LDIR) -lft -o $(NAME) -I minilibx/ -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

%.o: $(SRCS_DIR)%.c $(INC)
	$(CC) -c $(CFLAGS) -I./$(LINC) -I ./ $<

$(LIBFT): $(LDIR)
	make -C $(LDIR)
clean:
	@rm -f $(OBJ_LIST)
	@make clean -C $(LDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LDIR)

re: fclean all

.PHONY: all clean fclean re
