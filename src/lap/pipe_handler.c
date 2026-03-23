/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:44 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:39 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

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
