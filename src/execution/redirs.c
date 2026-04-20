/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:43 by texenber          #+#    #+#             */
/*   Updated: 2026/04/20 12:40:49 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/lap.h"

// things needed for the redir loop
// 1. in parsing once we find a redir that matches <, <<, >>, > we need to add it to the linked list of exec_redirs.
// 2. as long as there is a redir and we are still in the same CMD we are gonna keep on adding the redirs into the exec_redirs linked list.
// 3. the delimiter for the exec_redirs is a pipe that signifies the start of a new cmd which would also start a new exec_redir list.
// 4. make sure that exec_redirs = NULL is possible because we can have a list of cmds without redirs.
// 5. the exec_redirs struct can be initialized as a NULL inside the new_cmd function and then once we create the function to handle the list we can malloc the list to the sizeof(t_exec_redirs)
// 6. we can use the handle_redirections function that allows us to go inside the functions that are handling each individual case for redirections <, <<, >>, >. and inside those functions we can call the function that makes or adds to the linked list. we can do this right before *token = next->next;.

t_exec_redir *new_redir(int type, char *filename)
{
	t_exec_redir	*node;

	node = malloc(sizeof(t_exec_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->filename = filename;
	node->next = NULL;

	return (node);
}

void add_redirs(t_cmd *cmds, t_exec_redir *node)
{
	t_exec_redir	*tmp;

	if (!cmds || !node)
		return ;
	if (!cmds->exec_redirs)
	{
		cmds->exec_redirs = node;
		return ;
	}
	tmp = cmds->exec_redirs;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = node;	
}

int	apply_heredoc(t_cmd *cmds)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	ft_putstr_fd(cmds->heredoc_content, fd[1]);
	close(fd[1]);
	
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	close (fd[0]);
	return (0);
}

int	apply_append(t_exec_redir *r)
{
	int fd;
	
	fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(r->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	apply_out(t_exec_redir *r)
{
	int fd;
	
	fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(r->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	apply_in(t_exec_redir *r)
{
	int fd;
	
	fd = open(r->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(r->filename);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (0);
}

int	apply_redirections(t_exec_redir *r, t_cmd *cmds)
{
	int	res;
	
	res = 0;
	if (r->type == TOKEN_REDIR_IN)
		res = apply_in(r);
	else if (r->type == TOKEN_REDIR_OUT)
		res = apply_out(r);
	else if (r->type == TOKEN_REDIR_OUT_APPEND)
		res = apply_append(r);
	else if (r->type == TOKEN_HEREDOC)
		res = apply_heredoc(cmds);
	return (res);
}


int	all_redirections(t_cmd *cmds)
{
	t_exec_redir	*r;
	int				res;

	r = cmds->exec_redirs;
	while (r)
	{
		res = apply_redirections(r, cmds);
		if (res == 1)
			return (1);
		r = r->next;
	}
	return (0);
}
