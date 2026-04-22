/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:04 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 12:24:07 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

int	scan_pipe(t_shell *shell, t_scan_ctx *cntx, int i)
{
	(void)shell;
	if (!add_token(cntx->head,
			(t_token_data){TOKEN_PIPE, &cntx->input[i], 1, cntx->has_space}))
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

int	scan_redirections(t_shell *shell, t_scan_ctx *cntx, int i)
{
	int	len;
	int	type;

	(void)shell;
	type = get_redir_type_len(cntx->input, i, &len);
	if (!type)
		return (i);
	if (create_redir(cntx->head,
			(t_redir){type, &cntx->input[i], len, cntx->has_space}))
		return (-1);
	return (i + len);
}
