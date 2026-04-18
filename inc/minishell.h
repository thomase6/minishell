/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:01:09 by texenber          #+#    #+#             */
/*   Updated: 2026/04/18 14:41:37 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// #define _DEFAULT_SOURCE

#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <limits.h>
#include "../libft/src/libft.h"


///		Global signal variable			///
extern volatile sig_atomic_t g_signal;

typedef struct s_exec_redir
{
	int					type;
	char				*content;

	struct s_exec_redir	*next;
	
}	t_exec_redir;

// this might be needed in case that heredoc requires an expansion itself.
//	int heredoc_fd;
//	int heredoc_expand:
//	s_redir *next;
// things needed for the redir loop
// 1. in parsing once we find a redir that matches <, <<, >>, > we need to add it to the linked list of exec_redirs.
// 2. as long as there is a redir and we are still in the same CMD we are gonna keep on adding the redirs into the exec_redirs linked list.
// 3. the delimiter for the exec_redirs is a pipe that signifies the start of a new cmd which would also start a new exec_redir list.
// 4. make sure that exec_redirs = NULL is possible because we can have a list of cmds without redirs.
// 5. the exec_redirs struct can be initialized as a NULL inside the new_cmd function and then once we create the function to handle the list we can malloc the list to the sizeof(t_exec_redirs)
// 6. we can use the handle_redirections function that allows us to go inside the functions that are handling each individual case for redirections <, <<, >>, >. and inside those functions we can call the function that makes or adds to the linked list. we can do this right before *token = next->next;.

typedef struct s_cmd
{
	char			**argv;				// command + args
	//		Parsing			//
	t_exec_redir	exec_redirs;	
	char			*infile;			// < infile
	char			*outfile;			// > or >> outfile
	int				append;				// 1 if >>, 0 if >
	char			*heredoc_delim;		// << delimter (parser only)
	int				heredoc_quoted;		// 1 if delimiter quoted
	char			*heredoc_content;	// << content lines
	//		Execution		//
	int				infile_fd;
	int				outfile_fd;
	int				is_builtin;
	
	struct s_cmd	*next;			// next command (pipe)
}   t_cmd;

typedef struct s_shell
{
	char	**env;
	int		last_status;
} t_shell;

///		initializing the envp copy		///
int		init_env(t_shell *shell, char **envp);

///		minishell cleanup				///
void	cleanup_shell(t_shell *shell);

///		signals in the main				///
void	setup_main_signals(void);
void	siginthandler(int sig);
int		signal_main_hook(void);

///		signals in execute				///
void	set_signals_for_child(void);
void	set_signals_for_parent(void);

#endif //MINISHELL_H
