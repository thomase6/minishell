/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:43 by texenber          #+#    #+#             */
/*   Updated: 2026/04/22 15:53:44 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

t_exec_redir	*new_redir(int type, char *filename)
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

void	add_redirs(t_cmd *cmds, t_exec_redir *node)
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
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
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
