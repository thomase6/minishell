/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:33:12 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/27 10:29:03 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static void	handle_syntax_helper(const char *token_str)
{
	if (ft_strcmp_lap(token_str, "<<") == 0)
		write (2, "minishell: syntax error: unexpected token '<<'\n", 48);
	else if (ft_strcmp_lap(token_str, ">>") == 0)
		write (2, "minishell: syntax error: unexpected token '>>'\n", 48);
	else if (ft_strcmp_lap(token_str, "<") == 0)
		write (2, "minishell: syntax error: unexpected token '<'\n", 47);
	else if (ft_strcmp_lap(token_str, ">") == 0)
		write (2, "minishell: syntax error: unexpected token '>'\n", 47);
	else if (ft_strcmp_lap(token_str, "|") == 0)
		write (2, "minishell: syntax error: unexpected token '|'\n", 47);
	else if (ft_strcmp_lap(token_str, "'") == 0
		|| ft_strcmp_lap(token_str, "\"") == 0)
		write (2, "minishell: syntax error: unmatched quote\n", 42);
	else
		write (2, "minishell: syntax error: unknown token\n", 40);
}

void	handle_syntax_error(const char *token_str, int missing_next)
{
	if (!token_str)
	{
		write (2, "minishell: syntax error: unknown error\n", 39);
		return ;
	}
	if (missing_next)
	{
		write (2, "minishell: syntax error: un token 'newline' after '", 52);
		write (2, token_str, ft_strlen_lap(token_str));
		write (2, "'\n", 2);
		return ;
	}
	handle_syntax_helper(token_str);
}
