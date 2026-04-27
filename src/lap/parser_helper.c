/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:42:41 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/23 12:59:53 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

int	handle_exit(char *res, size_t *j, t_shell *shell)
{
	char	*tmp;

	tmp = ft_itoa_lap(shell->last_status);
	if (!tmp)
		return (-1);
	ft_strcpy_lap(res + *j, tmp);
	*j += ft_strlen_lap(tmp);
	free(tmp);
	return (0);
}

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

int	join_last_arg(t_cmd *current, char *val)
{
	int		last;
	char	*tmp;

	last = 0;
	while (current->argv[last + 1])
		last++;
	tmp = ft_strjoin_lap(current->argv[last], val);
	if (!tmp)
		return (0);
	free(current->argv[last]);
	current->argv[last] = tmp;
	return (1);
}
