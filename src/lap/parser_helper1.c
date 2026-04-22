/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:38 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 09:17:30 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

/* ===================== Redirection Handlers ===================== */

int	handle_exit(char *res, size_t *j, t_shell *shell)
{
	char	*tmp;

	tmp = ft_itoa_lap(shell->last_status);
	if (!tmp)
		return (-1);
	ft_strcpy_lap(res + *j, tmp);
	*j += ft_strlen_lap(tmp);
	free(tmp);
	return (0);
}

static t_exec_redir	*create_in_redir(char *value)
{
	char	*dup;
	t_exec_redir	*new;

	dup = ft_strdup_lap(value);
	if (!dup)
		return (NULL);
	new = new_redir(TOKEN_REDIR_IN, dup);
	if (!new)
		free(dup);
	return (new);
}

int	handle_redir_in(t_cmd *cmd, t_token **token)
{
	t_token			*next;
	t_exec_redir	*new;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	if (!cmd->infile)
		cmd->infile = ft_strdup_lap(next->value);
	if (!cmd->infile && !next->value)
		return (-1);
	new = create_in_redir(next->value);
	if (!new)
		return (-1);
	add_redirs(cmd, new);
	*token = next->next;
	return (0);
}
/*
int	handle_redir_in(t_cmd *cmd, t_token **token)
{
	t_token			*next;
	t_exec_redir	*new;
	char			*dup;
	char			*dup2;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (!cmd->infile)
		cmd->infile = dup;
	else
		free(dup);
	dup2 = ft_strdup_lap(next->value);
	if (!dup2)
	{
		free (dup);
		return (-1);
	}
	new = new_redir(TOKEN_REDIR_IN, dup2);
	if (!new)
	{
		free (dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	*token = next->next;
	return (0);
}
*/

int	handle_redir_out(t_cmd *cmd, t_token **token)
{
	t_token			*next;
	t_exec_redir	*new;
	char			*dup;
	char			*dup2;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (!cmd->outfile)
	{
		cmd->outfile = dup;
		cmd->append = 0;
	}
	else
		free(dup);
	dup2 = ft_strdup_lap(next->value);
	if (!dup2)
		return (-1);
	new = new_redir(TOKEN_REDIR_OUT, dup2);
	if (!new)
	{
		free (dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	*token = next->next;
	return (0);
}

int	handle_redir_out_append(t_cmd *cmd, t_token **token)
{
	t_token			*next;
	t_exec_redir	*new;
	char			*dup;
	char			*dup2;

	if (!cmd || !token || !*token)
		return (-1);
	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
		return (-1);
	dup = ft_strdup_lap(next->value);
	if (!dup)
		return (-1);
	if (!cmd->outfile)
	{
		cmd->outfile = dup;
		cmd->append = 1;
	}
	else
		free(dup);
	dup2 = ft_strdup_lap(next->value);
	if (!dup2)
		return (-1);
	new = new_redir(TOKEN_REDIR_OUT_APPEND, dup2);
	if (!new)
	{
		free (dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	*token = next->next;
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
			add_args_cmd(current, tokens->value);
		tokens = tokens->next;
	}
	return (cmd_list);
}
