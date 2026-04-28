/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 13:07:26 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

int	ft_intlen(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

size_t	handle_var(t_expand_ctx *ctx)
{
	char	*tmp;
	size_t	start;
	size_t	var_len;

	start = ctx->i + 1;
	var_len = 0;
	while (ctx->val[start + var_len]
		&& (ft_isalnum_lap(ctx->val[start + var_len])
			|| ctx->val[start + var_len] == '_'))
		var_len++;
	tmp = my_getenv_len(&ctx->val[start], var_len, ctx->shell->env);
	if (!tmp)
		tmp = "";
	ctx->j += ft_strlen_lap(ft_strcpy_lap(ctx->res + ctx->j, tmp));
	return (var_len);
}

int	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC && tmp->next
			&& tmp->next->type == TOKEN_WORD)
		{
			tmp = tmp->next;
			tmp = tmp->next;
			continue ;
		}
		if (expand_token_value(tmp, shell) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
