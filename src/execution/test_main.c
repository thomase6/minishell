#include "../../inc/minishell.h"

//test main for the executor.
int main(int argc, char **argv, char **envp)
{
    t_cmd a;
    t_cmd b;
    t_cmd c;
    t_shell shell; //this will hold our tmp env and last status used.
    char *cmd1[] = {"env",NULL};
    char *cmd2[] = {"grep","SHLVL", NULL};
    char *cmd3[] = {"pwd", NULL};
    int status;

    a.argv = cmd1;
    a.infile = -1;
    a.outfile = -1;
    a.is_builtin = 1;
    // a.next = &b;
    a.next = NULL;

    b.argv = cmd2;
    b.infile = -1;
    b.outfile = -1;
    b.is_builtin = 0;
    // b.next = &c;
    b.next = NULL;

    c.argv = cmd3;
    c.infile = -1;
    c.outfile = -1;
    c.is_builtin = 1;
    c.next = NULL;

    // if (init_env(&shell, envp) == -1)
    // {
    //     ft_putstr_fd("Error: failed to initialize\n", 2);
	//     return (1);
    // }
    execute_cmds(&a, envp, &status); // CHANGE: add t_shell *shell
    // free_argv(shell.env);
    // printf("exit status: %d\n", status);
}

// void test_cd(char **argv, int test_num, char **envp)
// {
//     t_cmd cmd;
//     int status;
//     char *before;
//     char *after;
    
//     before = getcwd(NULL, 0);
    
//     printf("=== Test %d ===\n", test_num);
//     printf("Before: %s\n", before);
    
//     cmd.argv = argv;
//     cmd.infile = -1;
//     cmd.outfile = -1;
//     cmd.is_builtin = 1;
//     cmd.next = NULL;
    
//     execute_cmds(&cmd, envp, &status);
    
//     after = getcwd(NULL, 0);
//     printf("After:  %s\n", after);
//     printf("Status: %d\n\n", status);
    
//     free(before);
//     free(after);
// }
// int main(int argc, char **argv, char **envp)
// {
//     char *test1[] = {"cd", "/tmp", NULL};
//     char *test2[] = {"cd", "..", NULL};
//     char *test3[] = {"cd", NULL};
//     char *test4[] = {"cd", "/nonexistent", NULL};
//     char *test5[] = {"cd", ".", NULL};
    
//     test_cd(test1, 1, envp);
//     test_cd(test2, 2, envp);
//     test_cd(test3, 3, envp);
//     test_cd(test4, 4, envp);
//     test_cd(test5, 5, envp);
    
//     return (0);
// }



// int execute_cmds(t_cmd *cmds, char **envp, int *last_status)
// {
// 	if (!cmds)
// 		return (0);
// 	if (!cmds->next && cmds->is_builtin)
// 		return (exec_builtin_parent(cmds, envp, last_status));
// 	return (exec_pipeline(cmds, envp, last_status));
// }

// int	cmd_check(char *path, char *cmd)
// {
// 	if (access(path, F_OK) != 0)
// 	{
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		free(path);
// 		return (127);
// 	}
// 	if (access(path, X_OK) != 0)
// 	{
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": permission denied\n", 2);
// 		free(path);
// 		return (126);
// 	}
// 	return (0);
// }

// void	close_all(int prev_fd, int fd[2])
// {
// 	if (prev_fd != -1) 
// 		close(prev_fd);
// 	if (fd[0] != -1)
// 	{
// 		close(fd[0]);
// 		fd[0] = -1;
// 	}
// 	if (fd[1] != -1)
// 	{
// 		close(fd[1]);
// 		fd[1] = -1;
// 	}	
// }

// int wait_all(int *last_status) 
// {
// 	int		status;
// 	pid_t	pid;
// 	int		last;

// 	last = 0;
// 	while((pid = wait(&status)) > 0)
// 	{
// 		if (WIFEXITED(status)) 
// 			last = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status)) 
// 			last = 128 + WTERMSIG(status);
// 	}
// 	*last_status = last;
// 	return (last);
// }


// void	exec_child(t_cmd *cmds, char **envp, int prev_fd, int fd[2])
// {
// 	char	*path;
// 	int		err;

// 	if (cmds->infile != -1)
// 	{
// 		dup2(cmds->infile, STDIN_FILENO);
// 		close(cmds->infile);
// 	}
// 	else if (prev_fd != -1)
// 		dup2(prev_fd, STDIN_FILENO);
// 	if (cmds->outfile != -1)
// 	{
// 		dup2(cmds->outfile, STDOUT_FILENO);
// 		close(cmds->outfile);
// 	}
// 	else if (cmds->next)
// 		dup2(fd[1], STDOUT_FILENO);

// 	close_all(prev_fd, fd);

// 	if (!cmds->argv || !cmds->argv[0] || cmds->argv[0][0] == '\0') 
// 	{
// 		ft_putstr_fd("minishell:command not found", 2);
// 		exit(127);
// 	}
// 	if (cmds->is_builtin)
// 		exit(exec_builtin(cmds, envp));
// 	path = resolve_path(cmds->argv[0], envp);
// 	err = cmd_check(path, cmds->argv[0]);
// 	if (err != 0)
// 		exit(err);
// 	execve(path, cmds->argv, envp);
// 	free(path);
// 	exit(127);
// }	

// int	exec_pipeline(t_cmd *cmds, char **envp, int *last_status)
// {
// 	int		fd[2];
// 	int		prev_fd = -1;
// 	pid_t	pid;

// 	while (cmds)
// 	{
// 		fd[0] = -1;
// 		fd[1] = -1;
// 		if (cmds->next && pipe(fd) < 0)
// 		{
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			*last_status = 1;
// 			return (-1);
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 		{
// 			if (fd[0] != -1)
// 				close(fd[0]);
// 			if (fd[1] != -1)
// 				close(fd[1]);
// 			if (fd[prev_fd] != -1)
// 				close(fd[prev_fd]);
// 			*last_status = 1;
// 			return (-1);
// 		}
// 		if (pid == 0)
// 			exec_child(cmds, envp, prev_fd, fd);
// 		if (cmds->infile != -1)
// 			close(cmds->infile);
// 		if (cmds->outfile != -1)
// 			close(cmds->outfile);
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (cmds->next)
// 		{
// 			close(fd[1]);
// 			prev_fd = fd[0];
// 		}
// 		cmds = cmds->next;
// 	}
// 	return (wait_all(last_status));
// }

// void	free_argv(char **av)
// {
// 	int	i;

// 	i = 0;
// 	while (av[i])
// 	{
// 		free (av[i]);
// 		i++;
// 	}
// 	if (av)
// 		free (av);
// }

// char	*resolve_cmd(char *cmd, char **dir_path)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*result;

// 	i = -1;
// 	result = NULL;
// 	while (dir_path[++i])
// 	{
// 		tmp = ft_strjoin(dir_path[i], "/");
// 		result = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (!result)
// 			return (NULL);
// 		if (access(result, X_OK) == 0)
// 			return (result);
// 		free (result);
// 	}
// 	return (ft_strdup(cmd));
// }

// char	*resolve_path(char *cmd, char **envp) 
// {
// 	char	*env_path;
// 	char	*result;
// 	char	**dir_path;
// 	int		i;

// 	i = 0;
// 	env_path = NULL;
// 	if (ft_strchr(cmd, '/'))
// 		return (ft_strdup(cmd));
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			env_path = envp[i] + 5;
// 			break ;
// 		}
// 		i++;
// 	}
// 	dir_path = ft_split(env_path, ':');
// 	if (!dir_path)
// 		return (ft_strdup(cmd));
// 	result = resolve_cmd(cmd, dir_path);
// 	if (dir_path)
// 		free_argv(dir_path);
// 	return (result);
// }

// int	exec_builtin(t_cmd *cmds, char **envp)
// {
// 	if (ft_strncmp(cmds->argv[0], "echo", 4) == 0)
// 		return(builtin_echo(cmds->argv));
// 	else if (ft_strncmp(cmds->argv[0], "cd", 2) == 0)
// 		return(builtin_cd(cmds->argv, envp));
// 	else if (ft_strncmp(cmds->argv[0], "pwd", 3) == 0)
// 		return(builtin_pwd());
// 	else if (ft_strncmp(cmds->argv[0], "env", 3) == 0)
// 		return(builtin_env(envp));
// 	else if (ft_strncmp(cmds->argv[0], "exit", 4) == 0)
// 		return(builtin_exit(cmds->argv));	
// 	return (0);
// }

// int	exec_builtin_parent(t_cmd *cmds, char **envp, int *last_status)
// {
// 	int res = exec_builtin(cmds, envp);
// 	*last_status = res;
// 	return (res);
// }

// int	builtin_pwd(void)
// {
// 	char *cwd;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		perror("pwd");
// 		return (1);
// 	}
// 	ft_putstr_fd(cwd, 1);
// 	ft_putchar_fd('\n', 1);
// 	free(cwd);
// 	return (0);
// }

// int	builtin_exit(char **argv)
// {
// 	int exit_code;
// 	int	i;

// 	ft_putstr_fd("exit\n", 2);

// 	if (!argv[1])
// 		exit(0); //change for the last_status later once the function has been changed
// 	i = 0;
// 	if (argv[1][i] == '+' || argv[1][i] == '-')
// 		i++;
// 	while (argv[1][i])
// 	{
// 		if(!ft_isdigit(argv[1][i]))
// 		{
// 			ft_putstr_fd("exit: ", 2);
// 			ft_putstr_fd(argv[1], 2);
// 			ft_putstr_fd(": numeric argument required\n", 2);
// 			exit (255);
// 		}
// 		i++;
// 	}
// 	if (argv[2])
// 	{
// 		ft_putstr_fd("exit: too many arguments\n", 2);
// 		return (1);
// 	}
// 	exit_code = ft_atoi(argv[1]);
// 	exit(exit_code % 256);
// }

// int	builtin_env(char **envp)
// {
// 	int i;

// 	if (!envp)
// 		return (1);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_putstr_fd(envp[i], 1);
// 		ft_putchar_fd('\n', 1);
// 		i++;
// 	}
// 	return (0);
// }

// int	builtin_echo(char **argv)
// {
// 	int i;
// 	int n_flag;
// 	int j;

// 	i = 1;
// 	n_flag = 0;
// 	while (argv[i] && argv[i][0] == '-' && argv[i][1] == 'n')
// 	{
// 		j = 1;
// 		while (argv[i][j] == 'n')
// 			j++;
// 		if (argv[i][j] == '\0')
// 		{
// 			n_flag = 1;
// 			i++;
// 		}
// 		else 
// 			break;
// 	}
// 	while (argv[i])
// 	{
// 		ft_putstr_fd(argv[i],1);
// 		if (argv[i + 1] != NULL)
// 			ft_putchar_fd(' ', 1);
// 		i++;
// 	}
// 	if (!n_flag)
// 		ft_putchar_fd('\n',1);
// 	return (0);
// }


// int	builtin_cd(char **av, char **envp)
// {
// 	char	*path;
// 	char	*home;
// 	int		i;

// 	if (!av[1])
// 	{
// 		home = NULL;
// 		i = 0;
// 		while (envp[i])
// 		{
// 			if (ft_strncmp(envp[i], "HOME=", 5) == 0)
// 			{
// 				home = envp[i] + 5;
// 				break;
// 			}
// 			i++;
// 		}
// 		if (!home)
// 		{
// 			ft_putstr_fd("cd: HOME not set\n", 2);
// 			return (1);
// 		}
// 		path = home;
// 	}
// 	else
// 		path = av[1];

// 	if (chdir(path) != 0)
// 	{
// 		ft_putstr_fd("cd: ", 2);
// 		ft_putstr_fd(path, 2);
// 		ft_putstr_fd(": ", 2);
// 		perror("");
// 		return (1);
// 	}
// 	return (0);
// }

