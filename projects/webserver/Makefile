# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 10:25:12 by asacchin          #+#    #+#              #
#    Updated: 2025/10/02 12:35:13 by dde-giov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webServer

CC := c++
FLAGS := -Wall -Wextra -Werror -std=c++98
RM := rm -f

OBJSDIR = objects

# COLORS
CLR_RMV := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
CYAN := \033[1;36m

SRC := srcs/Server.cpp srcs/utils.cpp \
	srcs/Request.cpp srcs/Response.cpp \
	srcs/ConfigParser.cpp srcs/Config.cpp \
	srcs/CgiState.cpp

SRCMAIN := srcs/main.cpp
SRCSOCKMAIN := srcs/test_socket_main.cpp
SRCPARSER := srcs/ConfigParser.cpp srcs/ParserMain.cpp

OBJS := $(addprefix $(OBJSDIR)/, $(SRC:.cpp=.o))
OBJMAIN := $(addprefix $(OBJSDIR)/, $(SRCMAIN:.cpp=.o))
OBJSOCKMAIN := $(addprefix $(OBJSDIR)/, $(SRCSOCKMAIN:.cpp=.o))
OBJSPARSER := $(addprefix $(OBJSDIR)/, $(SRCPARSER:.cpp=.o)) 
 
all: $(NAME)

$(OBJSDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "$(BLUE)Compiling: $(CLR_RMV)$<"
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJMAIN)
	@echo "$(GREEN)Linking $(CLR_RMV)of $(YELLOW)$(NAME)$(CLR_RMV)..."
	@$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "$(GREEN)$(NAME) created ✔️$(CLR_RMV)"


parser: $(OBJS) $(OBJSPARSER)
	@echo "$(GREEN)Linking socket test version$(CLR_RMV)..."
	@$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "$(GREEN)$(NAME) (socket test) created ✔️$(CLR_RMV)"
	@echo "$(CYAN)Run with: ./$(NAME)$(CLR_RMV)"

socket: $(OBJS) $(OBJSOCKMAIN)
	@echo "$(GREEN)Linking socket test version$(CLR_RMV)..."
	@$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "$(GREEN)$(NAME) (socket test) created ✔️$(CLR_RMV)"
	@echo "$(CYAN)Run with: ./$(NAME)$(CLR_RMV)"

clean:
	@$(RM) -r $(OBJSDIR)
	@echo "$(RED)Removed objects ✔️$(CLR_RMV)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(NAME) ✔️$(CLR_RMV)"

cleandir: fclean
	@$(RM) -r errors uploads tmp
re: fclean all

.PHONY: all clean fclean re socket parser cleandir