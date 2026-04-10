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

static int check_pipe(t_shell *shell, t_token *curr, t_token *head)
{
    // Pipe at the start or end
    if (curr == head && !curr->next)
        handle_syntax_error(shell, "|", 0); // lone pipe
    else if (curr == head || !curr->next)
        handle_syntax_error(shell, "|", 0); // pipe at start or pipe at end
    // Consecutive pipes
    else if (curr->next->type == TOKEN_PIPE)
        handle_syntax_error(shell, "|", 0);
    else
        return 0; // valid pipe usage

    return 1; // syntax error
}

static int	check_redirection(t_shell *shell, t_token *curr)
{
	if (!curr->next || curr->next->type != TOKEN_WORD)
	{
		if (!curr->next)
			handle_syntax_error(shell, curr->value, 1);
		else
			handle_syntax_error(shell, curr->next->value, 0);
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
int	validate_syntax(t_shell *shell, t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE && check_pipe(shell, curr, head))
			return (1);
		if (is_redirection(curr->type) && check_redirection(shell, curr))
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
