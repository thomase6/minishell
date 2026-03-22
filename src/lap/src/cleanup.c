/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:28:31 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 10:20:24 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
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
		if (tmp->heredoc_content)        // 🔹 FREE HEREDOC CONTENT
			free(tmp->heredoc_content);
		free(tmp);
	}
}
