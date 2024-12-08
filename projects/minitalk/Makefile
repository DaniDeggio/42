
NAME_S = server
SRC_S = server.c
OBJ_S = $(SRC_S.o=.c)

NAME_C = client
SRC_C = client.c
OBJ_C = $(SRC_C.o=.c)

LIBRARY := libft/libft.a ft_printf/libftprintf.a
FTPRINTF := ft_printf/
LIBFT := libft/

FLAG = -Wall -Werror -Wextra
CC = gcc

all : 
		make -C $(FTPRINTF)
		make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_S) $(LIBRARY) -o $(NAME_S)
	$(CC) $(CFLAGS) $(SRC_C) $(LIBRARY) -o $(NAME_C)

server :
		make -C $(FT_PRINTF)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(SRC_S) $(LIBRARY) -o $(NAME_S)

client :
		make -C $(FT_PRINTF)
		make -C $(LIBFT)
		$(CC) $(CFLAGS) $(SRC_C) $(LIBRARY) -o $(NAME_C)

clean: 
	make fclean -C $(FTPRINTF)
	make fclean -C $(LIBFT)
	rm -f $(OBJ_C)
	rm -f $(OBJ_S)
	
fclean:	clean
	make clean
	rm -f $(NAME_S)
	rm -f $(NAME_C)

re:	fclean all clean

.PHONY: all clean fclean re
