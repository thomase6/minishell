/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:09 by texenber          #+#    #+#             */
/*   Updated: 2026/03/23 10:03:59 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/src/libft.h"
#include "./execution.h"

typedef struct s_shell
{
	char	**env;
	int		last_status;
} t_shell;

///		initializing the envp copy		///
int		init_env(t_shell *shell, char **envp);

///		minishell cleanup				///
void	cleanup_shell(t_shell *shell);

#endif //MINISHELL_H