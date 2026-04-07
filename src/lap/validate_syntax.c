/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:00:03 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/06 16:20:26 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static int	check_pipe(t_token *curr, t_token *head)
{
	if (curr == head || !curr->next || curr->next->type == TOKEN_PIPE)
	{
		if (!curr->next || curr->next->type != TOKEN_PIPE)
			handle_syntax_error("|", 1);
		else
			handle_syntax_error("|", 0);
		return (1);
	}
	return (0);
}

static int	check_redirection(t_token *curr)
{
	if (!curr->next || curr->next->type != TOKEN_WORD)
	{
		if (!curr->next)
			handle_syntax_error(curr->value, 1);
		else
			handle_syntax_error(curr->next->value, 0);
		return (1);
	}
	return (0);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_OUT_APPEND
		|| type == TOKEN_HEREDOC);
}

int	validate_syntax(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE && check_pipe(curr, head))
			return (1);
		if (is_redirection(curr->type) && check_redirection(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_cmd	*handle_pipe(t_cmd *current)
{
	t_cmd	*new;

	if (!current)
		return (NULL);
	new = new_cmd();
	if (!new)
		return (NULL);
	current->next = new;
	return (new);
}
