/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:05:46 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:27:54 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	ft_cd(char **args, t_minir *mini)
{
	char	*tmp;
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	if (args[1] == NULL || args[1][0] == '~')
	{
		tmp = getenv("HOME");
		chdir(tmp);
		if (args[1][1] != '\0')
		{
			if (chdir(args[1] + 2) == -1)
			{
				chdir(pwd);
				return (read_file_error(mini, args[1], 1));
			}
		}
	}
	else if (chdir(args[1]) == -1)
		return (read_file_error(mini, args[1], 1));
	getcwd(pwd, sizeof(pwd));
	tmp = ft_strjoin("PWD=", pwd);
	add_var(tmp, mini);
	free(tmp);
	return (0);
}

int	ft_env(t_minir *mini)
{
	t_listc	*env;

	env = mini->env_list;
	while (env)
	{
		printf("%s\n", (char *)env->cont);
		env = env->next;
	}
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	if (args[1] && !strcmp(args[1], "-n"))
	{
		newline = 1;
		i++;
	}
	else
		newline = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (!newline)
	{
		printf("\n");
	}
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("getcwd error!", 2);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
