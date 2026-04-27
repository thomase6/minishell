/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:24:55 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/23 13:35:11 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

static int	validate_redir_out(t_cmd *cmd, t_token **token, t_token **next)
{
	if (!cmd || !token || !*token)
		return (-1);
	*next = (*token)->next;
	if (!*next || (*next)->type != TOKEN_WORD)
		return (-1);
	return (0);
}

static int	set_outfile(t_cmd *cmd, char **dup, char *value)
{
	*dup = ft_strdup_lap(value);
	if (!*dup)
		return (-1);
	if (!cmd->outfile)
	{
		cmd->outfile = *dup;
		cmd->append = 0;
	}
	else
		free(*dup);
	return (0);
}

static int	create_redir_out(t_cmd *cmd, char *value)
{
	t_exec_redir	*new;
	char			*dup2;

	dup2 = ft_strdup_lap(value);
	if (!dup2)
		return (-1);
	new = new_redir(TOKEN_REDIR_OUT, dup2);
	if (!new)
	{
		free(dup2);
		return (-1);
	}
	add_redirs(cmd, new);
	return (0);
}

int	handle_redir_out(t_cmd *cmd, t_token **token)
{
	t_token	*next;
	char	*dup;

	if (validate_redir_out(cmd, token, &next) == -1)
		return (-1);
	if (set_outfile(cmd, &dup, next->value) == -1)
		return (-1);
	if (create_redir_out(cmd, next->value) == -1)
		return (-1);
	*token = next->next;
	return (0);
}
