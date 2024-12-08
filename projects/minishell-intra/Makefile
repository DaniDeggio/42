
# BASIC
CC = cc -g
CSANI = cc -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
RLFLAG = -lreadline
RM = rm -rf

# LIBFT
LIBFT = ./includes/libft/libft.a

#miniHELL
NAME = minishell
SRC =	sources/tokenaizer/cpy_word.c \
		sources/utils/signals_01.c \
		sources/utils/01_utils.c \
		sources/cmd/export2.c \
		sources/executer/read_file.c \
		sources/tokenaizer/ft_strlen_custom.c \
		sources/executer/ecxeve.c \
		sources/error/03_error_mixed.c \
		sources/executer/exec.c \
		sources/tokenaizer/token_in_array.c \
		sources/cmd/builtin.c \
		sources/utils/debugg.c \
		sources/tokenaizer/expander.c \
		sources/parsing/parser.c \
		sources/executer/redir.c \
		sources/error/06_wrong_dollar_02.c \
		sources/error/01_error_quotes.c \
		sources/tokenaizer/single_token_matrix.c \
		sources/utils/02_utils.c \
		sources/cmd/localvar.c \
		sources/error/05_wrong_dollar.c \
		sources/error/00_verify_readline.c \
		sources/utils/01a_utils.c \
		sources/utils/03_utils.c \
		sources/error/error_begin_02.c \
		sources/executer/redirections.c \
		sources/free/00_free.c \
		sources/cmd/cmd.c \
		sources/cmd/exit.c \
		sources/cmd/export.c \
		sources/cmd/do_builtin.c \
		sources/executer/pipe.c \
		sources/cmd/unset.c \
		sources/utils/list_utils.c \
		sources/tokenaizer/itoa_custom.c \
		sources/error/02_error_start_last.c \
		sources/utils/signals_02.c \
		sources/minishell.c \
		sources/tokenaizer/count_words.c \
		sources/utils/prompt.c \
		sources/error/03a_error_mixed.c \
		sources/tokenaizer/init_token_count.c \
		sources/error/04a_error_messages.c \
		sources/error/04_error_messages.c \
		sources/utils/00_utils.c \
		sources/init/init.c \
		sources/tokenaizer/cpy_word_utils.c \
		sources/error/05a_wrong_dollar.c \
		sources/tokenaizer/arr3.c \


OBJSDIR = objects
OBJ = $(addprefix $(OBJSDIR)/, $(SRC:.c=.o))

# MAKE RULES
all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./includes/libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
	echo "Everything Done!"

sani: re $(OBJ)
	$(MAKE) -C ./libft
	$(CSANI) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
	echo "Compiled with fsanitizer"

$(OBJSDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE)	clean -C ./includes/libft

fclean: clean
	$(RM) $(NAME) $(SANI) $(OBJSDIR)
	$(MAKE) fclean -C ./includes/libft
	echo "Everything Deleted..."

re: fclean all

.PHONY: all clean fclean re
