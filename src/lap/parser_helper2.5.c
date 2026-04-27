/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:27:37 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/23 12:32:52 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

int	append_heredoc(t_heredoc *tmp)
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

void	expand_heredoc_line(char **line, t_shell *shell)
{
	t_token	tmp_token;

	tmp_token.value = *line;
	tmp_token.quoted = 0;
	expand_token_value(&tmp_token, shell);
	*line = tmp_token.value;
}

/* Read heredoc content with variable expansion for unquoted delimiters */

int	handle_sigint(char *line, char *content, t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		if (line)
			free(line);
		if (content)
			free(content);
		setup_main_signals();
		shell->last_status = 130;
		return (1);
	}
	return (0);
}

int	is_delimiter(char *line, const char *delimiter)
{
	if (ft_strcmp_lap(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	process_line(t_heredoc *tmp, const char *delimiter,
						int quoted, t_shell *shell)
{
	if (handle_sigint(tmp->line, tmp->content, shell))
		return (0);
	if (!tmp->line)
		return (0);
	if (is_delimiter(tmp->line, delimiter))
		return (0);
	if (!quoted)
		expand_heredoc_line(&tmp->line, shell);
	if (!append_heredoc(tmp))
		return (0);
	free(tmp->line);
	return (1);
}
