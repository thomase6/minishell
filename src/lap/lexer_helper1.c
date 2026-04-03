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

int	scan_single_quote(const char *input, int i, t_token **head, int has_space)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '\'')
		i++;
	if (!input[i])
	{
		handle_syntax_error("'", 0);
		return (-1);
	}
	tok = add_token(head, (t_token_data){TOKEN_WORD,
			&input[start], i - start, has_space});
	if (!tok)
		return (-1);
	tok->quoted = 1;
	return (i + 1);
}

int	scan_double_quote(const char *input, int i, t_token **head, int has_space)
{
	int		start;
	t_token	*tok;

	start = i + 1;
	i = start;
	while (input[i] && input[i] != '"')
		i++;
	if (!input[i])
	{
		handle_syntax_error("\"", 0);
		return (-1);
	}
	tok = add_token(head, (t_token_data){TOKEN_WORD,
			&input[start], i - start, has_space});
	if (!tok)
		return (-1);
	tok->quoted = 2;
	return (i + 1);
}

char	*remove_quotes_str(const char *str)
{
	size_t	len;
	char	*res;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup_lap(""));
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		res = malloc(len - 1);
		if (!res)
			return (NULL);
		ft_memcpy_lap(res, str + 1, len - 2);
		res[len - 2] = '\0';
		return (res);
	}
	return (ft_strdup_lap(str));
}
