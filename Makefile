NAME = lem-in
CC = gcc
#CFLAGS = -Wall -Wextra -Werror


IDIR = incs/
LDIR = libft/
LINC = $(LDIR)incs
LIBFT = $(LDIR)libft.a
INC = lem_in.h

SRCS_DIR = srcs/
SRCS_LIST=\
		main.c\
		mover.c\
		solver.c\
		put_error.c\
		tools.c\
		s_vertex.c\
		s_ants.c\
		s_edge.c\
		s_path.c\
		s_mx.c

OBJ = $(SRCS_LIST:%.c=%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L $(LDIR) -lft -o $(NAME)

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
