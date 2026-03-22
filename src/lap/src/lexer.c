/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:28:57 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/02 11:28:58 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(const char *input)
{
	int		i;
	t_token	*head;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
			i++;
		else if (input[i] == '\'')
			SCAN_OR_BREAK(scan_single_quote(input, i, &head));
		else if (input[i] == '"')
			SCAN_OR_BREAK(scan_double_quote(input, i, &head));
		else if (input[i] == '|')
			SCAN_OR_BREAK(scan_pipe(input, i, &head));
		else if (input[i] == '<' || input[i] == '>')
			SCAN_OR_BREAK(scan_redirections(input, i, &head));
		else
			SCAN_OR_BREAK(scan_word(input, i, &head));
	}
	return (head);
}

/*
t_token	*lexer(const char *input)
{
	t_token	*head = NULL;
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '\'')
		{
			i = check_scan(scan_single_quote(input, i, &head), &head);
			if (i == -1)
				break;
		}
		else if (input[i] == '"')
		{
			i = check_scan(scan_double_quote(input, i, &head), &head);
			if (i == -1)
				break;
		}
		else if (input[i] == '|')
		{
			i = check_scan(scan_pip(input, i, &head), &head);
			if (i == -1)
				break;
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			i = check_scan(scan_redirections(input, i, &head), &head);
			if (i == -1)
				break;
		}
		else
		{
			i = check_scan(scan_word(input, i, &head), &head);
			if (i == -1)
				break;
		}
	}
	return (head);
}
*/
