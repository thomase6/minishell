/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:59:18 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 09:24:53 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->exec_redirs = NULL;
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_quoted = 0;
	cmd->heredoc_content = NULL;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->is_builtin = 0;
	cmd->next = NULL;
	return (cmd);
}

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

char	**add_args(char **argv, char *word)
{
	int		i;
	int		j;
	char	**new;

	if (!word)
		return (argv);
	i = argv_len(argv);
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = argv[j];
		j++;
	}
	new[i] = ft_strdup_lap(word);
	new[i + 1] = NULL;
	if (argv)
		free(argv);
	return (new);
}

int	add_args_cmd(t_cmd *cmd, char *arg)
{
	if (!cmd || !arg)
		return (0);
	cmd->argv = add_args(cmd->argv, arg);
	return (cmd->argv != NULL);
}

char	*my_getenv(char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	if (!name || !envp)
		return (NULL);
	len = 0;
	while (name[len])
		len++;
	while (envp[i])
	{
		if (ft_strncmp_lap(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
