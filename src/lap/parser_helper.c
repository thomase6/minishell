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

static int	ft_intlen(int n)
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

static size_t	handle_var(t_expand_ctx *ctx)
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

static int	handle_dollar(t_expand_ctx *ctx)
{
	size_t	len;

	if (ctx->val[ctx->i + 1] == '?')
	{
		handle_exit(ctx->res, &ctx->j, ctx->shell);
		ctx->i += 2;
	}
	else if (ft_isalnum_lap(ctx->val[ctx->i + 1])
		|| ctx->val[ctx->i + 1] == '_')
	{
		len = handle_var(ctx);
		ctx->i += len + 1;
	}
	else
	{
		ctx->res[ctx->j++] = ctx->val[ctx->i++];
	}
	return (0);
}

static void	fill_expanded(char *res, char *val, t_shell *shell)
{
	t_expand_ctx	ctx;

	ctx.res = res;
	ctx.val = val;
	ctx.i = 0;
	ctx.j = 0;
	ctx.shell = shell;
	while (ctx.val[ctx.i])
	{
		if (ctx.val[ctx.i] == '$')
			handle_dollar(&ctx);
		else
			ctx.res[ctx.j++] = ctx.val[ctx.i++];
	}
	ctx.res[ctx.j] = '\0';
}

static size_t	handle_dollar_len(char *val, size_t *i, t_shell *shell)
{
	size_t	start;
	size_t	var_len;
	char	*tmp;

	if (val[*i + 1] == '?')
	{
		*i += 2;
		return (ft_intlen(shell->last_status));
	}
	else if (ft_isalnum_lap(val[*i + 1]) || val[*i + 1] == '_')
	{
		start = *i + 1;
		var_len = 0;
		while (val[start + var_len]
			&& ft_isalnum_lap(val[start + var_len]))
			var_len++;
		tmp = my_getenv_len(&val[start], var_len, shell->env);
		*i = start + var_len;
		if (tmp)
			return (ft_strlen_lap(tmp));
		return (0);
	}
	(*i)++;
	return (1);
}

static size_t	get_expanded_len(char *val, t_shell *shell)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (val[i])
	{
		if (val[i] == '$')
			len += handle_dollar_len(val, &i, shell);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int	expand_token_value(t_token *t, t_shell *shell)
{
	char	*res;
	size_t	len;

	if (!t || !t->value || t->quoted == 1)
		return (0);
	len = get_expanded_len(t->value, shell);
	res = malloc(len + 1);
	if (!res)
		return (-1);
	fill_expanded(res, t->value, shell);
	free(t->value);
	t->value = res;
	return (1);
}

int	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;
	t_token	*prev;

	prev = NULL;
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
