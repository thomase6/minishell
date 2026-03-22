/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:44 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/09 12:03:12 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
