/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 15:50:46 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 15:53:49 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"


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
	int	fd;

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
	int	fd;

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
	int	fd;

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