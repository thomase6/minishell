/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:09 by texenber          #+#    #+#             */
/*   Updated: 2026/03/26 13:22:46 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// #define _DEFAULT_SOURCE

#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/src/libft.h"
#include "./execution.h"
#include <signal.h>
#include <sys/ioctl.h>

///		Global signal variable			///
extern volatile sig_atomic_t g_signal;

typedef struct s_shell
{
	char	**env;
	int		last_status;
} t_shell;

///		initializing the envp copy		///
int		init_env(t_shell *shell, char **envp);

///		minishell cleanup				///
void	cleanup_shell(t_shell *shell);

///		signals							///
void	setup_main_signals(struct sigaction *sa);
void	siginthandler(int sig);
int		signal_main_hook(void);

#endif //MINISHELL_H