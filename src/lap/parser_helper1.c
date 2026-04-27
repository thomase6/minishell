/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:38 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/23 13:26:34 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"
#include "../../inc/execution.h"

t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;

	cmd_list = NULL;
	current = NULL;
	while (tokens)
	{
		if (!cmd_list)
		{
			cmd_list = new_cmd();
			current = cmd_list;
		}
		if (tokens->type == TOKEN_PIPE)
		{
			current->next = new_cmd();
			current = current->next;
		}
		else
			add_args_cmd(current, tokens->value);
		tokens = tokens->next;
	}
	return (cmd_list);
}
