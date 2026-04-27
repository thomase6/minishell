/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:24:21 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/23 13:32:32 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

static int	validate_redir_in(t_cmd *cmd, t_token **token, t_token **next)
{
	if (!cmd || !token || !*token)
		return (-1);
	*next = (*token)->next;
	if (!*next || (*next)->type != TOKEN_WORD)
		return (-1);
	return (0);
}

static int	set_infile(t_cmd *cmd, char **dup, char *value)
{
	*dup = ft_strdup_lap(value);
	if (!*dup)
		return (-1);
	if (!cmd->infile)
		cmd->infile = *dup;
	else
		free(*dup);
	return (0);
}

static int	create_redir_in(t_cmd *cmd, char *value, char *dup)
{
	t_exec_redir	*new;
	char			*dup2;

	dup2 = ft_strdup_lap(value);
	if (!dup2)
	{
		free(dup);
		return (-1);
	}
	new = new_redir(TOKEN_REDIR_IN, dup2);
	if (!new)
	{
		free(dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	return (0);
}

int	handle_redir_in(t_cmd *cmd, t_token **token)
{
	t_token	*next;
	char	*dup;

	if (validate_redir_in(cmd, token, &next) == -1)
		return (-1);
	if (set_infile(cmd, &dup, next->value) == -1)
		return (-1);
	if (create_redir_in(cmd, next->value, dup) == -1)
		return (-1);
	*token = next->next;
	return (0);
}
