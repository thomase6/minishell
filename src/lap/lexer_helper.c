/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:04 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:11 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

int	scan_pipe(const char *input, int i, t_token **head, int has_space)
	{
	if (!add_token(head, (t_token_data){TOKEN_PIPE, &input[i], 1, has_space}))
		return (-1);
	return (i + 1);
}

static int	create_redir(t_token **head, t_redir redir)
{
	if (!add_token(head, (t_token_data){redir.type,
			redir.input, redir.len, redir.has_space}))
		return (-1);
	return (0);
}

static int	get_redir_type_len(const char *input, int i, int *len)
{
	if (input[i] == '<' && input[i + 1] == '<')
	{
		*len = 2;
		return (TOKEN_HEREDOC);
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		*len = 2;
		return (TOKEN_REDIR_OUT_APPEND);
	}
	else if (input[i] == '>')
	{
		*len = 1;
		return (TOKEN_REDIR_OUT);
	}
	else if (input[i] == '<')
	{
		*len = 1;
		return (TOKEN_REDIR_IN);
	}
	*len = 0;
	return (0);
}

int	scan_redirections(const char *input, int i,
		t_token **head, int has_space)
{
	int	len;
	int	type;

	type = get_redir_type_len(input, i, &len);
	if (!type)
		return (i);
	if (create_redir(head, (t_redir){type, &input[i], len, has_space}))
		return (-1);
	return (i + len);
}
