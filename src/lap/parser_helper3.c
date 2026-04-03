/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:59:18 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/03 10:59:43 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_quoted = 0;
	cmd->heredoc_content = NULL;
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
	char	*clean_word;

	if (!word)
		return (argv);
	clean_word = remove_quotes_str(word);
	if (!clean_word)
		return (NULL);
	i = argv_len(argv);
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (free(clean_word), NULL);
	j = 0;
	while (j < i)
	{
		new[j] = argv[j];
		j++;
	}
	new[i] = clean_word;
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

/*
static char *my_getenv(char *name, char **envp)
{
	int	i;
	size_t	len;

	i = 0;
	if (!name || !envp)
		return (NULL);
	len = 0;
	while (name[len])
		len++;
	while (envp[i])
	{
		// compare the first len characters and make sure next char is '='
		if (ft_strncmp_lap(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1); // skip the '='
        	}
		i++;
	}
	return (NULL); // not found
}
*/
