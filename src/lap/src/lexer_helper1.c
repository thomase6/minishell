/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:25:02 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 11:04:18 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	scan_single_quote(const char *input, int i, t_token **head)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '\'')
		i++;
	if (!input[i])
		return (-1);
	tok = add_token(head, TOKEN_WORD, &input[start], i - start);
	if (!tok)
		return (-1);
	tok->quoted = 1;
	return (i + 1);
}

int	scan_double_quote(const char *input, int i, t_token **head)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '"')
		i++;
	if (!input[i])
		return (-1);
	tok = add_token(head, TOKEN_WORD, &input[start], i - start);
	if (!tok)
		return (-1);
	tok->quoted = 2;
	return (i + 1);
}
