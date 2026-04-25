/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:50:59 by texenber          #+#    #+#             */
/*   Updated: 2026/04/25 10:34:34 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	free_redirs(t_exec_redir *redir)
{
	t_exec_redir	*tmp;

	if (!redir)
		return ;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->filename)
		{
			free(tmp->filename);
			tmp->filename = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
}

// this function frees the cmd arguments and closes the fd's
// if they are still open for each cmd
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->argv)
			free_argv(tmp->argv);
		if (tmp->exec_redirs)
			free_redirs(tmp->exec_redirs);
		if (tmp->heredoc_delim)
		{
			free(tmp->heredoc_delim);
			tmp->heredoc_delim = NULL;
		}
		if (tmp->heredoc_content)
		{
			free(tmp->heredoc_content);
			tmp->heredoc_content = NULL;
		}
		if (tmp->infile)
		{
			free(tmp->infile);
			tmp->infile = NULL;
		}	
		if (tmp->outfile)
		{
			free(tmp->outfile);
			tmp->outfile = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

// this function just frees a double pointer
void	free_argv(char **av)
{
	int	i;

	i = 0;
	if (av == NULL)
		return ;
	while (av[i])
	{
		free (av[i]);
		av[i] = NULL;
		i++;
	}
	if (av)
	{
		free (av);
		av = NULL;
	}
}
