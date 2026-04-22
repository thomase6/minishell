/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:42:41 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 13:42:48 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

void	merge_adjacent_tokens(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;
	char	*joined;

	tmp = tokens;
	while (tmp && tmp->next)
	{
		next = tmp->next;
		if (tmp->type == TOKEN_WORD && next->type == TOKEN_WORD
			&& !next->has_space_before)
		{
			joined = ft_strjoin_lap(tmp->value, next->value);
			free(tmp->value);
			tmp->value = joined;
			tmp->next = next->next;
			free(next->value);
			free(next);
			continue ;
		}
		tmp = tmp->next;
	}
}
