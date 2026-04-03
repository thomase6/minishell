/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:28:57 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:17 by texenber         ###   ########.fr       */
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

t_token	*lexer(const char *input)
{
	int		i;
	int		has_space;
	t_token	*head;

	head = NULL;
	i = 0;
	while (input[i])
	{
		has_space = skip_white_spaces(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '\'')
			SCAN_OR_BREAK(scan_single_quote(input, i, &head, has_space));
		else if (input[i] == '"')
			SCAN_OR_BREAK(scan_double_quote(input, i, &head, has_space));
		else if (input[i] == '|')
			SCAN_OR_BREAK(scan_pipe(input, i, &head, has_space));
		else if (input[i] == '>' || input[i] == '<')
			SCAN_OR_BREAK(scan_redirections(input, i, &head, has_space));
		else
			SCAN_OR_BREAK(scan_word(input, i, &head, has_space));
	}
	return (head);
}
