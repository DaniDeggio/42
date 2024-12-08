NAME = so_long

SRC =  so_long.c\
		movement/movement.c movement/movement_utils.c\
		map/check_map.c map/map.c map/print_map.c map/map_utils.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		libft/ft_strlen.c libft/ft_itoa.c \
		utils/utils.c utils/animation.c\

OBJ = $(SRC.c=.o)

LIBRARY := -Lminilibx -lmlx -framework OpenGL -framework AppKit ft_printf/libftprintf.a
MINILIBX := minilibx/
FTPRINTF := ft_printf/

FLAG = -Wall -Werror -Wextra
CC = gcc

all : 
		make -C $(FTPRINTF)
	$(CC) $(CFLAGS) $(SRC) $(LIBRARY) -o $(NAME) -lz -g

clean: 
	make fclean -C $(FTPRINTF)
	rm -f $(OBJ)
	
fclean:	clean
	rm -f $(NAME)

re:	fclean all clean

.PHONY: all clean fclean re
