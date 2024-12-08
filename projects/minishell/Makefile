# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deggio <deggio@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:14:49 by dde-giov          #+#    #+#              #
#    Updated: 2023/12/12 18:00:44 by deggio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/minishell.c\

OBJ = ${SRC:.c=.o}

CC = gcc -Wall -Wextra -Werror -g

FLAGS = -lreadline

LIBFT = include/libft/
LIBRARY = include/libft/libft.a

.c.o:
	@${CC} -c $< -o ${<:.c=.o}      

all	: $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(OBJ) $(LIBRARY) -o $(NAME) $(FLAGS)

clean :
	@rm -f $(OBJ)
	@make clean -C $(LIBFT)
	
fclean : clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)	
re : fclean all

.PHONY: all clean fclean re