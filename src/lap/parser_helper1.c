/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:38 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/30 15:09:13 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

/* ===================== Redirection Handlers ===================== */

int	handle_redir_in(t_cmd *cmd, t_token **token)
{
	t_token	*next;
	char	*dup;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = dup;
	*token = next;
	return (0);
}

int	handle_redir_out(t_cmd *cmd, t_token **token)
{
	t_token	*next;
	char	*dup;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = dup;
	cmd->append = 0;
	*token = next;
	return (0);
}

int	handle_redir_out_append(t_cmd *cmd, t_token **token)
{
	t_token	*next;
	char	*dup;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = dup;
	cmd->append = 1;
	*token = next;
	return (0);
}

/* ===================== Build Commands ===================== */

t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;

	cmd_list = NULL;
	current = NULL;
	while (tokens)
	{
		if (!cmd_list)
		{
			cmd_list = new_cmd();
			current = cmd_list;
		}
		if (tokens->type == TOKEN_PIPE)
		{
			current->next = new_cmd();
			current = current->next;
		}
		else
		{
			add_args_cmd(current, tokens->value);
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
