/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:10:40 by deggio            #+#    #+#             */
/*   Updated: 2023/12/12 16:31:54 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "include/libft/libft.h"

typedef struct	s_data
{
    char		**input;
}				t_data;

#endif