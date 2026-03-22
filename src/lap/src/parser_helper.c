/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 11:14:03 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**add_args(char **argv, char *word)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	if (argv)
		while (argv[i])
			i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = argv[j];
		j++;
	}
	new[i] = ft_strdup(word);
	if (!new[i])
	{
		free(new);
		return (NULL);
	}
	new[i + 1] = NULL;
	if (argv)
		free(argv);
	return (new);
}
/* count existing arguments-> allocate new array old + new + NULL
 ->copy old arg-> add new word -> free old argv array , not the string inside
*/

int	add_args_cmd(t_cmd *cmd, char *arg)
{
	if (!cmd || !arg)
		return (0);
	cmd->argv = add_args(cmd->argv, arg);
	return (cmd->argv != NULL);
}

/*
 * Expand a single token value ($VAR or $?) in-place
 */
static int	expand_token_value(t_token *token, char **envp, int last_exit)
{
	char	*val;
	char	*new_val;
	char	*env_val;

	(void)envp;
	if (!token || !token->value)
		return (0);
	val = token->value;
	if (val[0] == '$')
	{
		if (val[1] == '?' && val[2] == '\0')
		{
			new_val = ft_itoa(last_exit);
			if (!new_val)
				return (-1);
			free(token->value);
			token->value = new_val;
		}
		else if (val[1] != '\0')
		{
			env_val = getenv(&val[1]);   // make function getenv
			if (!env_val)
				env_val = ft_strdup("");
			else
				env_val = ft_strdup(env_val);
			if (!env_val)
				return (-1);
			free(token->value);
			token->value = env_val;
		}
	}
	return (0);
}

/*
 * Expand tokens linked list while parsing
 */
int	expand_tokens(t_token *tokens, char **envp, int last_exit)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (expand_token_value(tmp, envp, last_exit) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
/*

char *my_getenv(char *name, char **envp)
{
    int i = 0;
    size_t len = 0;

    if (!name || !envp)
        return NULL;

    len = 0;
    while (name[len])
        len++;

    while (envp[i])
    {
        // compare the first len characters and make sure next char is '='
        if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
        {
            return envp[i] + len + 1; // skip the '='
        }
        i++;
    }
    return NULL; // not found
}
*/
