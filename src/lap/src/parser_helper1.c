/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:38 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 11:18:09 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	dup = ft_strdup(next->value);
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
	dup = ft_strdup(next->value);
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
	dup = ft_strdup(next->value);
	if (!dup)
		return (-1);
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = dup;
	cmd->append = 1;
	*token = next;
	return (0);
}

/* ===================== Helpers ===================== */

/* Append a line + newline to existing content */
static char	*append_line(char *content, const char *line)
{
	char	*tmp;

	tmp = ft_strjoin(content, line);
	if (!tmp)
		return (NULL);
	free(content);
	content = tmp;
	tmp = ft_strjoin(content, "\n");
	if (!tmp)
	{
		free(content);
		return (NULL);
	}
	free(content);
	return (tmp);
}

/* Simple variable expansion for heredoc (supports $? and $VAR) */
static char	*expand_line(const char *line, int last_exit)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?')
			{
				tmp = ft_itoa(last_exit);
				result = ft_strjoin_free(result, tmp);
				free(tmp);
				i += 2;
				continue;
			}
			else
			{
				int start = i + 1;
				int len = 0;
				while (line[start + len] && line[start + len] != ' ' && line[start + len] != '$')
					len++;
				char *var_name = ft_substr(line, start, len);
				char *val = NULL;
				if (var_name)
				{
					val = getenv(var_name);
					val = val ? ft_strdup(val) : ft_strdup("");
					free(var_name);
				}
				tmp = val ? val : ft_strdup("");
				result = ft_strjoin_free(result, tmp);
				free(tmp);
				i += len + 1;
				continue;
			}
		}
		tmp = malloc(2);
		if (!tmp)
			return (result);
		tmp[0] = line[i];
		tmp[1] = '\0';
		result = ft_strjoin_free(result, tmp);
		free(tmp);
		i++;
	}
	return (result);
}

/* ===================== Heredoc Handler ===================== NEED TO USE READLINE !!! FIX !!! */

int handle_heredoc(t_cmd *cmd, t_token **token, int last_exit)
{
    t_token *cur;
    char *line_to_add;
    char *new_content;
    
    if (!cmd || !token || !*token)
        return (-1);
    cur = (*token)->next;
    if (!cur || cur->type != TOKEN_WORD)
        return (-1);
    // Set heredoc delimiter
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->heredoc_delim = ft_strdup(cur->value);
    cmd->heredoc_quoted = cur->quoted;
    // Initialize heredoc content
    if (cmd->heredoc_content)
        free(cmd->heredoc_content);
    cmd->heredoc_content = ft_strdup("");
    if (!cmd->heredoc_content)
        return (-1);
    cur = cur->next;
    while (cur && !(cur->type == TOKEN_WORD && ft_strcmp(cur->value, cmd->heredoc_delim) == 0))
    {
        // Expand variables only if delimiter is unquoted
        if (cmd->heredoc_quoted == 0)
            line_to_add = expand_line(cur->value, last_exit);
        else
            line_to_add = ft_strdup(cur->value);

        if (!line_to_add)
            return (-1);

        // Append line safely using append_line (handles memory)
        new_content = append_line(cmd->heredoc_content, line_to_add);
        free(line_to_add);

        if (!new_content)
	{
   	 	free(cmd->heredoc_content);
   	 	cmd->heredoc_content = NULL;
    		return (-1);
	}
        cmd->heredoc_content = new_content;
        cur = cur->next;
    }

    // Move token pointer past the delimiter
    if (cur)
        cur = cur->next;

    *token = cur;
    return 0;
}

/* ===================== Build Commands ===================== */

t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*cmd_list = NULL;
	t_cmd	*current = NULL;

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
