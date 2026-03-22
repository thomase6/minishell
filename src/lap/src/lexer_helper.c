/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:04 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 11:03:08 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_token(t_token **head, t_token_type type,
		const char *value, int len)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strndup(value, len);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int	scan_word(const char *input, int i, t_token **head)
{
	int		start;
	t_token	*tok;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '"'
		&& input[i] != '\'' && input[i] != '\n')
		i++;
	tok = add_token(head, TOKEN_WORD, &input[start], i - start);
	if (!tok)
		return (-1);
	tok->quoted = 0;
	return (i);
}

int	scan_pipe(const char *input, int i, t_token **head)
{
	if (!add_token(head, TOKEN_PIPE, &input[i], 1))
		return (-1);
	return (i + 1);
}

int	scan_redirections(const char *input, int i, t_token **head)
{
	if (input[i] == '<' && input[i + 1] == '<')
	{
		if (!add_token(head, TOKEN_HEREDOC, &input[i], 2))
			return (-1);
		return (i + 2);
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		if (!add_token(head, TOKEN_REDIR_OUT_APPEND, &input[i], 2))
			return (-1);
		return (i + 2);
	}
	else if (input[i] == '>')
	{
		if (!add_token(head, TOKEN_REDIR_OUT, &input[i], 1))
			return (-1);
		return (i + 1);
	}
	else if (input[i] == '<')
	{
		if (!add_token(head, TOKEN_REDIR_IN, &input[i], 1))
			return (-1);
		return (i + 1);
	}
	return (i);
}
