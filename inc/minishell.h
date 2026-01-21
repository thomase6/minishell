/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:09 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 10:01:10 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/src/libft.h"
#include "./execution.h"

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// } t_env;

typedef struct s_shell
{
	char	**env;
	int		last_status;
} t_shell;

// typedef struct s_cmd
// {
// 	char			**av;
// 	char			*path;
// 	int				fd_in;
// 	int				fd_out;
// 	bool			is_builtin;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }	t_cmd;

// typedef struct s_minishell
// {
// 	char	**env;
// 	char	*input;
// 	char	**output;
// 	int		error_code;
// 	// t_parser	*parser; gotta add this once the lexer struct is added
// 	// t_exec	execut; add with expand struct
// }	t_minishell;

///		initializing the envp copy		///
int	init_env(t_shell *shell, char **envp);

#endif //MINISHELL_H