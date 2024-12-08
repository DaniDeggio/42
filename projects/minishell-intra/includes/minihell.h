/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:24:31 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:27:01 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal;

# define RESET "\033[0m"
# define RED_BOLD "\033[1;31m"
# define VIOLET_BOLD "\033[1;35m"
// variables

# ifdef __linux__
#  define PATH_MAX 4096
# elif __MACH__
#  define PATH_MAX 1024
# else
#  warning "Unknown or unsupported operating system. Assuming PATH_MAX is 4096."
#  define PATH_MAX 4096
# endif

# define READ_END 0
# define WRITE_END 1

# define ERROR_UNCLOSED "minihell : syntax error unclosed quotes\n"
# define ERROR_PIPE "minihell : syntax error  near '|'\n"

typedef struct s_listc
{
	char			*cont;
	int				id;
	struct s_listc	*next;
}			t_listc;

typedef struct s_minir
{
	int			nb_tokens;
	char		**split_arr;
	int			y;
	int			x;
	char		**arr2;
	int			y2;
	int			x2;
	char		**arr3;
	int			y3;
	int			flag3;
	int			count;
	int			count_words;
	int			flag_cmd_valid;
	int			flag_quote;
	int			flag_err_quote;
	int			flag_err_type;
	int			flag_to_do;
	int			nb_pipes;
	int			**pipesfd;
	int			pipe_index;
	int			red_fd;
	pid_t		pid;
	char		**paths;
	char		**env;
	int			write_to_pipe;
	int			read_from_pipe;
	int			read_from_file;
	int			redir;
	int			heredoc;
	int			skip;
	int			i_redir;
	int			i_readfile;
	int			frirst_redir;
	int			y_mx_envp;
	int			xenvp;
	int			i;
	int			mem_space;
	char		*check_exp;
	int			len_call_exp;
	int			nb_dol;
	int			*flag_dol;
	int			i_flag_dol;
	int			*save_node_id;
	int			flag_list;
	int			exit_code;
	t_listc		*env_list;
	int			index_list;
	t_listc		*local_var;
}	t_minir;

int			process_special_token(t_minir *mini, char *s, int i);
int			check_s_d_quotes(char *s, int i);
void		create_array(char *s, t_minir *mini);
char		*get_token(char *s);
void		check_next_special_token(char *s, int i, char **token);
void		get_cmd_matrix(char *s, t_minir *mini, int flag);
void		create_matrix_cmd(char *s, t_minir *mini);
char		*get_cmd_token(char *s, t_minir *mini);
void		line_to_cmd(char *s, t_minir *mini);
void		check_cmd_tokens(char *s, t_minir *mini);
int			ft_strlen_custom(char *s, int flag, t_minir *mini);
void		ft_count_exp_print_error(t_minir *mini);
void		ft_strlen_dble_quotes(char *s, t_minir *mini);
void		ft_strlen_no_quotes(char *s, t_minir *mini);
int			copy_exit_code(t_minir *mini, int i);
int			copy_no_quotes(char *s, int i, t_minir *mini, int len_name_var);
void		ft_count_words(char *s, t_minir *mini);
int			copy_dble_quotes(char *s, int i,
				t_minir *mini, int len_name_var);
char		*ft_write_word(char *s, t_minir *mini, int flag, int i);
int			ft_strlen_name_var(char *s, int *i, int len_name_var);
int			copy_dble_dollar(int i, t_minir *mini);
int			check_single_quotes(char *s, int len, int i, t_minir *mini);
int			check_dble_quotes(char *s, int len, int i, t_minir *mini);
int			check_no_space(char *s, int len, int i, t_minir *mini);
int			count_quotes(char *s);
int			error_begin(char *str, t_minir *mini);
int			error_end(char *s, char c, t_minir *mini);
int			check_2nd_char_02(char *s, int i, char d, t_minir *mini);
int			check_2nd_char_03(char *s, int i, char d, t_minir *mini);
int			check_spaces(char *s, int *i, t_minir *mini);
void		init_param(t_minir *mini);
int			ft_intsize(int n);
int			ft_ispositive(int n);
void		ft_itoa_custom(int n, t_minir *mini);
char		*get_var_cont(char *full_var);
int			error_begin_02(char *s, t_minir *mini);
int			check_next_chars(char *s, t_minir *mini);
int			return_negative(t_minir *mini);
void		init_splitarr(char *s, t_minir *mini);
void		ft_remove_node(t_listc **env_list, char *arg);
void		ft_exit_custom(t_minir *mini);
int			ft_exit_02(t_minir *mini);
void		reset_flags(t_minir *mini);
void		next_step_sub2(t_minir *mini);
void		next_step_sub(t_minir *mini);
int			check_next_step(t_minir *mini);
void		red_index(t_minir *mini);
void		command(t_minir *mini);
int			ft_ecxev(char *path, char **arg, char **env);
int			absolute_exec(t_minir *mini);
int			bin_exec(t_minir *mini, char **arr);
int			find_paths(t_minir *mini);
t_listc		*ft_lstlastc(t_listc *lst);
void		count_expanded_token(t_minir *mini, char *s);
void		count_expanded_token_local_var(t_minir *mini);
char		*prompt(void);
void		set_signal(void);
void		envp_to_matrix(t_minir *mini);
int			matrix_len(char **matrix);
void		add_index_to_local_var(t_minir *mini);
void		make_matrix(char *s, t_minir *mini);
int			verify_readline(char *s, t_minir *mini);
int			ft_isspace(char *s);
void		add_index_to_custom_env(t_minir *mini);
int			set_next_flag(t_minir *mini);
int			error_mixed_start(char *s, t_minir *mini);
int			find_i(char *s, int i);
void		check_child(int signum);
int			check_extra_char(char *s, int i, t_minir *mini);
int			check_next_arg(char *s, int i, t_minir *mini);
void		command_not_found(char *str, t_minir *mini);
int			error_dollar(char *s, t_minir *mini);
int			error_dollar_02(char *s, int i, t_minir *mini);
int			error_dollar_03(char *check_envp, t_minir *mini, int len);
int			do_execve(t_minir *mini);
int			exec(t_minir *mini);
int			count_pipes(t_minir *mini);
void		init_pipes(t_minir *mini);
void		insert_between_node(t_listc *prev, char *cont);
char		*get_var_name(char *full_var);
void		add_index_to_env_list(t_minir *mini);
void		reinit_param(t_minir *mini, char **envp);
void		init(t_minir *mini, char **envp);
void		start_env(char **envp, t_minir *mini);
void		split_init(char *s, t_minir *mini);
int			count_tokens(char *s, t_minir *mini);
int			get_token_01(char *s, int j);
void		copy_expanded_str(t_minir *mini, int start);
int			count_dollar_sign(char *s, t_minir *mini);
int			check_2nd_char(char *s, int i, t_minir *mini);
int			count_dble_quotes(char *s);
char		*removeplus(char *full_var);
int			var_name_length(char *full_var);
char		*var_noquot(char *str);
void		set_signal_child(void);
void		set_signal_avoid(void);
void		signal_heredoc_handler(void);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_strcpy(char *destination, const char *source);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
t_listc		*copy_env_in_list(char **env);
t_listc		*sort_listc(t_listc *list);
int			check_s_signal(char *s, t_minir *mini);
int			free_arr(char **arr);
void		ft_delete_matrix(void *matrix);
void		free_mx_envp(t_minir *mini);
int			ft_export(char **args, t_minir *mini);
void		check_duplicate(t_minir *mini, char *cont);
int			ft_unset(char **args, t_minir *mini);
int			add_on_env_02(char *arg, t_listc *local_list);
void		write_to_pipe(t_minir *mini);
int			add_on_env_03(char *cont, t_listc *env_list, int append);
void		error_dollar_02_a(char *s, int *i, int *len);
void		read_from_pipe(t_minir *mini);
void		close_pipeline(t_minir *mini);
int			error_dollar_00(char *s, int i, t_minir *mini);
int			return_not_required(t_minir *mini);
int			check_builtin(t_minir *mini);
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(t_minir *mini);
int			check_extra_char_2(char e, t_minir *mini);
int			check_read_file(t_minir *mini);
int			red_input(t_minir *mini, char *path);
int			heredoc(t_minir *mini);
int			heredoc_read(t_minir *mini, char *eof);
int			ft_lstsizec(t_listc *lst);
int			read_from_file(t_minir *mini);
int			check_redir(t_minir *mini);
int			error_dollar_01(char *s, t_minir *mini);
int			redir(t_minir *mini);
int			create_file(t_minir *mini, char *str, int redir);
int			do_red(t_minir *mini);
void		reset_flags2(t_minir *mini);
int			frist_redir(t_minir *mini);
void		get_arr2(char *s, t_minir *mini, int flag);
int			return_pipe_error(t_minir *mini);
int			return_gt_error(t_minir *mini);
int			return_lt_error(t_minir *mini);
int			return_nl_error(t_minir *mini);
int			exit__err(char *str, t_minir *mini);
void		error_dollar_02_b(char *check_envp, int *j,
				int *len, t_minir *mini);
int			count_single_quotes(char *s);
int			read_file_error(t_minir *mini, char *file, int flag);
void		free_list(t_listc *listc);
t_listc		*ft_lstnewc(void *content);
void		ft_lstadd_backc(t_listc **lst, t_listc *new);
int			do_builtin(t_minir *mini);
int			do_child_cmd(t_minir *mini);
void		get_arr3(t_minir *mini);
int			count_arr3(t_minir *mini);
void		init_arr3(t_minir *mini);
int			basic_export(t_minir *mini);
int			add_on_env(char *arg, t_minir *mini);
int			ft_cd(char **args, t_minir *mini);
int			add_var(char *str, t_minir *mini);
int			new_var(char *str, t_minir *mini, int add, int empty);
int			update_var(char *str, t_listc *list, int add);
#endif
