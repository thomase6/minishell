/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:28:31 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/23 10:21:08 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	check_scan(int i, t_token **head)
{
	if (i == -1)
	{
		free_tokens(*head);
		*head = NULL;
	}
	return (i);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*tmp;

	tmp = ft_strjoin_lap(s1, s2);
	free(s1);
	return (tmp);
}

static void	helper_free(t_cmd *tmp)
{
	size_t	i;

	if (!tmp)
		return ;
	if (tmp->argv)
	{
		i = 0;
		while (tmp->argv[i])
		{
			free(tmp->argv[i]);
			i++;
		}
		free(tmp->argv);
	}
	if (tmp->infile)
		free(tmp->infile);
	if (tmp->outfile)
		free(tmp->outfile);
	if (tmp->heredoc_delim)
		free(tmp->heredoc_delim);
	if (tmp->heredoc_content)
		free(tmp->heredoc_content);
}

void	free_cmds_lap(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		helper_free(tmp);
		free(tmp);
	}
}
