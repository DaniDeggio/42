# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:14:49 by dde-giov          #+#    #+#              #
#    Updated: 2023/10/12 20:54:46 by dde-giov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  push_swap.c\
		sorting.c sort_utils.c sorting_utils.c\
		utils.c stack_maker.c moves_ps.c moves_r.c moves_rr.c\
		ft_split.c libft_functions.c\

OBJ = ${SRC:.c=.o}
NAME = push_swap

SRC_B = checker.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJ_B =	${SRC_B:.c=.o}
NAME_B = checker
OUT = ${filter-out push_swap.o ,${OBJ}}

CC = gcc -Wall -Wextra -Werror -g
FT_PRINTF = ft_printf/
LIBRARY = ft_printf/libftprintf.a 

.c.o:
	@${CC} -c $< -o ${<:.c=.o}      

all	: $(NAME)

$(NAME) : $(OBJ)
	@make -C $(FT_PRINTF)
	@$(CC) $(OBJ) $(LIBRARY) -o $(NAME)

bonus : $(NAME) $(OBJ_B)
	@$(CC) $(OUT) $(OBJ_B) $(LIBRARY) -o $(NAME_B)

clean :
	@make clean -C $(FT_PRINTF)
	@rm -f $(OBJ)
	@rm -f $(OBJ_B)
	
fclean : clean
	@make fclean -C $(FT_PRINTF)
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	
re : fclean all bonus

.PHONY: all clean fclean re