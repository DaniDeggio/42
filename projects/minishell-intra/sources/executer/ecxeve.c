/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecxeve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:07 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	ft_ecxev(char *path, char **arg, char **env)
{
	char	pwd[PATH_MAX];

	if (access(path, X_OK))
		return (127);
	if (execve(path, arg, env) != 0)
	{
		getcwd(pwd, sizeof(pwd));
		if (chdir(path) != -1)
		{
			chdir(path);
			ft_putstr_fd("minishell: execve failed: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return (126);
		}
		ft_putstr_fd("minishell: execve failed: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Cannot be executed\n", 2);
		return (126);
	}
	return (0);
}

int	bin_exec(t_minir *mini, char **arr)
{
	char	**path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin("/", arr[0]);
	path = malloc(sizeof(char *) * (matrix_len(mini->paths) + 1));
	path[matrix_len(mini->paths)] = NULL;
	i = -1;
	while (mini->paths[++i])
		path[i] = ft_strjoin(mini->paths[i], tmp);
	free(tmp);
	i = -1;
	while (path[++i])
	{
		if (ft_ecxev(path[i], arr, mini->env) == 0)
			return (free_arr(path));
	}
	free_arr(path);
	return (127);
}
