/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:44 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 09:20:02 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

static char	*read_heredoc_content(const char *delimiter,
			int quoted, t_shell *shell)
{
	t_heredoc	tmp;

	tmp.line = NULL;
	tmp.content = NULL;
	tmp.new_content = NULL;
	tmp.content_len = 0;
	tmp.line_len = 0;
	setup_heredoc_signals();
	g_signal = 0;
	while (1)
	{
		tmp.line = readline("> ");
		if (!process_line(&tmp, delimiter, quoted, shell))
			break ;
	}
	setup_main_signals();
	return (tmp.content);
}

/* ===================== Handle Heredoc ===================== */

static int	validate_heredoc_input(t_cmd *cmd, t_token **token, t_token **cur)
{
	if (!cmd || !token || !*token)
		return (-1);
	*cur = (*token)->next;
	if (!*cur || (*cur)->type != TOKEN_WORD)
		return (-1);
	return (0);
}

static int	setup_heredoc_data(t_cmd *cmd, t_token *cur, t_shell *shell)
{
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup(cur->value);
	if (!cmd->heredoc_delim)
		return (-1);
	cmd->heredoc_quoted = cur->quoted;
	cmd->heredoc_content = read_heredoc_content(
			cmd->heredoc_delim, cur->quoted, shell);
	return (0);
}

static int	create_heredoc_redir(t_cmd *cmd, t_token *cur)
{
	t_exec_redir	*new;
	char			*dup2;

	dup2 = ft_strdup_lap(cur->value);
	if (!dup2)
		return (-1);
	new = new_redir(TOKEN_HEREDOC, dup2);
	if (!new)
	{
		free(dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	return (0);
}

int	handle_heredoc(t_cmd *cmd, t_token **token, t_shell *shell)
{
	t_token	*cur;

	if (validate_heredoc_input(cmd, token, &cur) == -1)
		return (-1);
	if (setup_heredoc_data(cmd, cur, shell) == -1)
		return (-1);
	if (create_heredoc_redir(cmd, cur) == -1)
		return (-1);
	*token = cur->next;
	return (0);
}
