/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:09 by texenber          #+#    #+#             */
/*   Updated: 2026/04/28 09:33:26 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// #define _DEFAULT_SOURCE

# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <limits.h>
# include "../libft/src/libft.h"

///		Global signal variable			///
extern volatile sig_atomic_t	g_signal;

typedef struct s_exec_redir
{
	int					type;
	char				*filename;

	struct s_exec_redir	*next;	
}	t_exec_redir;

typedef struct s_cmd
{
	char			**argv;				// command + args
	//		Parsing			//
	t_exec_redir	*exec_redirs;	
	char			*infile;			// < infile
	char			*outfile;			// > or >> outfile
	int				append;				// 1 if >>, 0 if >
	char			*heredoc_delim;		// << delimter (parser only)
	int				heredoc_quoted;		// 1 if delimiter quoted
	char			*heredoc_content;	// << content lines
	//		Execution		//
	// int				infile_fd;
	// int				outfile_fd;
	int				is_builtin;	
	struct s_cmd	*next;			// next command (pipe)
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		last_status;
}	t_shell;

///		initializing the envp copy		///
int		init_env(t_shell *shell, char **envp);

///		main loop						///
int	main_loop(t_shell *shell);

///		minishell cleanup				///
void	cleanup_shell(t_shell *shell);

///		signals in the main				///
void	setup_main_signals(void);
void	siginthandler(int sig);
int		signal_main_hook(void);
void	setup_heredoc_signals(void);

///		signals in execute				///
void	set_signals_for_child(void);
void	set_signals_for_parent(void);

#endif //MINISHELL_H
