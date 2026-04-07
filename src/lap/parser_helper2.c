/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:44 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/06 16:19:01 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

/* ===================== Join Last Argument ===================== */

int	join_last_arg(t_cmd *current, char *val)
{
	int		last;
	char	*tmp;

	last = 0;
	while (current->argv[last + 1])
		last++;
	tmp = ft_strjoin_lap(current->argv[last], val);
	if (!tmp)
		return (0);
	free(current->argv[last]);
	current->argv[last] = tmp;
	return (1);
}

/* ===================== Heredoc Helpers ===================== */

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
	ft_memcpy_lap(tmp->new_content + tmp->content_len,
		tmp->line, tmp->line_len);
	tmp->new_content[tmp->content_len + tmp->line_len] = '\n';
	tmp->new_content[tmp->content_len + tmp->line_len + 1] = '\0';
	tmp->content = tmp->new_content;
	tmp->content_len += tmp->line_len + 1;
	return (1);
}

/* Expand variables in a single line if needed */
static void	expand_heredoc_line(char **line, t_shell *shell)
{
	t_token	tmp_token;

	tmp_token.value = *line;
	tmp_token.quoted = 0;
	expand_token_value(&tmp_token, shell);
	*line = tmp_token.value;
}

/* Read heredoc content with variable expansion for unquoted delimiters */
static char	*read_heredoc_content(const char *delimiter,
			int quoted, t_shell *shell)
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
		if (!quoted)
			expand_heredoc_line(&tmp.line, shell);
		if (!append_heredoc(&tmp))
			return (NULL);
		free(tmp.line);
	}
	return (tmp.content);
}

/* ===================== Handle Heredoc ===================== */

int	handle_heredoc(t_cmd *cmd, t_token **token, t_shell *shell)
{
	t_token	*cur;

	if (!cmd || !token || !*token)
		return (-1);
	cur = (*token)->next;
	if (!cur || cur->type != TOKEN_WORD)
		return (-1);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup(cur->value);
	cmd->heredoc_quoted = cur->quoted;
	cmd->heredoc_content = read_heredoc_content(cmd->heredoc_delim,
			cur->quoted, shell);
	*token = cur->next;
	return (0);
}
