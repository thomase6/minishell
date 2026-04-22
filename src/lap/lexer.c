/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:28:57 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 12:22:52 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static int	skip_white_spaces(const char *input, int *i)
{
	int	has_space;

	has_space = 0;
	while (input[*i] == ' ' || input[*i] == '\t')
	{
		has_space = 1;
		(*i)++;
	}
	return (has_space);
}

static int	dispatch_scan(t_shell *shell, t_scan_ctx *cntx,
		const char *input, int i)
{
	if (input[i] == '\'')
		return (scan_single_quote(shell, cntx, i));
	else if (input[i] == '"')
		return (scan_double_quote(shell, cntx, i));
	else if (input[i] == '|')
		return (scan_pipe(shell, cntx, i));
	else if (input[i] == '>' || input[i] == '<')
		return (scan_redirections(shell, cntx, i));
	return (scan_word(shell, cntx, i));
}

t_token	*lexer(t_shell *shell, const char *input)
{
	int			i;
	int			has_space;
	int			res;
	t_token		*head;
	t_scan_ctx	cntx;

	head = NULL;
	i = 0;
	cntx.input = input;
	cntx.head = &head;
	while (input[i])
	{
		has_space = skip_white_spaces(input, &i);
		cntx.has_space = has_space;
		if (!input[i])
			break ;
		res = dispatch_scan(shell, &cntx, input, i);
		i = check_scan(res, &head);
		if (i == -1)
			return (NULL);
	}
	return (head);
}

t_token	*process_input(char *line, t_shell *shell)
{
	t_token	*tokens;

	if (!line || !shell)
		return (NULL);
	tokens = lexer(shell, line);
	if (!tokens)
		return (NULL);
	if (validate_syntax(shell, tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	if (expand_tokens(tokens, shell) == -1)
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}
