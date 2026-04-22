/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:33:12 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 09:44:44 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static void	put_err(const char *msg)
{
	write(2, ERR_PREFIX, ft_strlen_lap(ERR_PREFIX));
	write(2, msg, ft_strlen_lap(msg));
}

void	handle_syntax_error(t_shell *shell, const char *token_str,
				int missing_next)
{
	shell->last_status = 2;
	if (!token_str)
		return (put_err("unknown error\n"));
	write(2, ERR_PREFIX, ft_strlen_lap(ERR_PREFIX));
	write(2, "near unexpected token `", 23);
	if (missing_next)
		write(2, "newline", 7);
	else
		write(2, token_str, ft_strlen_lap(token_str));
	write(2, "'\n", 2);
}
