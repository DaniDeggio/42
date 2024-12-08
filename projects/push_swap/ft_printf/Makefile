# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 13:18:58 by dde-giov          #+#    #+#              #
#    Updated: 2023/02/08 15:43:54 by dde-giov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_printf.c ft_printf_utilies.c \

OBJS		=	${SRCS:.c=.o}

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	libftprintf.a

all:		${NAME}

$(NAME):	${OBJS}
					ar rc ${NAME} ${OBJS}

clean:
					${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
					${RM} ${NAME}

re:					fclean ${NAME}