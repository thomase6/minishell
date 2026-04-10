/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:25:02 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:14 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

int	scan_single_quote(t_shell *shell, const char *input, int i, t_token **head, int has_space)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '\'')
		i++;
	if (!input[i])
	{
		handle_syntax_error(shell, "'", 0);
		return (-1);
	}
	tok = add_token(head, (t_token_data){TOKEN_WORD,
			&input[start], i - start, has_space});
	if (!tok)
		return (-1);
	tok->quoted = 1;
	return (i + 1);
}

int	scan_double_quote(t_shell *shell, const char *input, int i, t_token **head, int has_space)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '"')
		i++;
	if (!input[i])
	{
		handle_syntax_error(shell, "\"", 0);
		return (-1);
	}
	tok = add_token(head, (t_token_data){TOKEN_WORD,
			&input[start], i - start, has_space});
	if (!tok)
		return (-1);
	tok->quoted = 2;
	return (i + 1);
}
