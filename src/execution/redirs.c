/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:00:43 by texenber          #+#    #+#             */
/*   Updated: 2026/04/18 14:59:00 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/lap.h"

// things needed for the redir loop
// 1. in parsing once we find a redir that matches <, <<, >>, > we need to add it to the linked list of exec_redirs.
// 2. as long as there is a redir and we are still in the same CMD we are gonna keep on adding the redirs into the exec_redirs linked list.
// 3. the delimiter for the exec_redirs is a pipe that signifies the start of a new cmd which would also start a new exec_redir list.
// 4. make sure that exec_redirs = NULL is possible because we can have a list of cmds without redirs.
// 5. the exec_redirs struct can be initialized as a NULL inside the new_cmd function and then once we create the function to handle the list we can malloc the list to the sizeof(t_exec_redirs)
// 6. we can use the handle_redirections function that allows us to go inside the functions that are handling each individual case for redirections <, <<, >>, >. and inside those functions we can call the function that makes or adds to the linked list. we can do this right before *token = next->next;.

void add_redirs_list(t_cmd *cmds, t_exec_redir *exec_redirs, t_token **tokens )
{
	t_exec_redir	*tmp;
	
//	if (exec_redirs == NULL)
//		tmp = malloc(sizeof(t_exec_redir));

//	if the list is not there we need to make sure to create it and set the current redir to the top of the redir list
//	once we have a list or have created the list we have to set the type to token->type and then the content to the next token->value and if needed quoted is also available inside of token
}