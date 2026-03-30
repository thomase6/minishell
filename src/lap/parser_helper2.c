/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:44 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/30 15:09:53 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

/* ===================== Helpers ===================== */
static int	append_heredoc(t_heredoc *tmp)
{
	tmp->line_len = ft_strlen_lap(tmp->line);
	tmp->new_content = malloc(tmp->content_len + tmp->line_len + 2);
	if (!tmp->new_content)
	{
		free(tmp->line);
		free(tmp->content);
		return (0);
	}
	if (tmp->content)
	{
		ft_memcpy_lap(tmp->new_content, tmp->content, tmp->content_len);
		free(tmp->content);
	}
	ft_memcpy_lap(tmp->new_content + tmp->content_len, tmp->line, tmp->line_len);
	tmp->new_content[tmp->content_len + tmp->line_len] = '\n';
	tmp->new_content[tmp->content_len + tmp->line_len + 1] = '\0';
	tmp->content = tmp->new_content;
	tmp->content_len += tmp->line_len + 1;
	return (1);
}

static char	*read_heredoc_content(const char *delimiter)
{
	t_heredoc	tmp;

	tmp.line = NULL;
	tmp.content = NULL;
	tmp.new_content = NULL;
	tmp.content_len = 0;
	tmp.line_len = 0;
	while (1)
	{
		tmp.line = readline("> ");
		if (!tmp.line || ft_strcmp_lap(tmp.line, delimiter) == 0)
		{
			free(tmp.line);
			break ;
		}
		if (!append_heredoc(&tmp))
			return (NULL);
		free(tmp.line);
	}
	return (tmp.content);
}

/* ====== Heredoc Handler NEED TO USE READLINE !!! FIX !!! === */

int	handle_heredoc(t_cmd *cmd, t_token **token, int last_exit)
{
	t_token	*cur;

	(void)last_exit;
	if (!cmd || !token || !*token)
		return (-1);
	cur = (*token)->next;
	if (!cur || cur->type != TOKEN_WORD)
		return (-1);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup_lap(cur->value);
	cmd->heredoc_quoted = cur->quoted;
	cmd->heredoc_content = read_heredoc_content(cmd->heredoc_delim);
	*token = cur->next;
	return (0);
}

t_cmd	*handle_pipe(t_cmd *current)
{
	t_cmd	*new;

	if (!current)
		return (NULL);
	new = new_cmd();
	if (!new)
		return (NULL);
	current->next = new;
	return (new);
}
