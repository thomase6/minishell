#ifndef EXECUTION_H
# define EXECUTION_H

#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/src/libft.h"

// typedef struct s_exec
// {
// 	char	*path;
// 	pid_t	*pids;
// 	size_t	ch_count;
// 	int		pipe_fd[2];
// 	int		*status;
// 	bool	is_builtin;
// }	t_exec;

typedef struct s_cmd
{
    char            **argv;
    int             infile;
    int             outfile;
    int             is_builtin;
    struct s_cmd    *next;
} t_cmd;

// int single_cmd_execution(char *av, char **envp);
int		execute_cmds(t_cmd *cmds, char **envp, int *last_status);
int		exec_pipeline(t_cmd *cmds, char **envp, int *last_status);
void	exec_child(t_cmd *cmds, char **envp, int prev_fd, int fd[2]);
char	*resolve_path(char *cmd, char **envp);
int		exec_builtin_parent(t_cmd *cmds, char **envp, int *last_status);
int		exec_builtin(t_cmd *cmds, char **envp);

/// builtin functions ///

int	builtin_echo(char **argv);
int	builtin_cd(char **av, char **envp);
int	builtin_pwd(void);
int	builtin_env(char **envp);
int	builtin_exit(char **argv);

///     exit and free       ///
void	free_argv(char **av);


#endif //EXECUTION_H