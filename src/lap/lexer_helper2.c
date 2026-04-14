/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:56:27 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/03 10:56:37 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static void	append_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*add_token(t_token **head, t_token_data data)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = data.type;
	new->value = ft_strndup_lap(data.value, data.len);
	if (!new->value)
		return (free(new), NULL);
	new->quoted = 0;
	new->has_space_before = data.has_space;
	new->next = NULL;
	append_token(head, new);
	return (new);
}

int	scan_word(const char *input, int i, t_token **head, int has_space)
{
	int		start;
	t_token	*tok;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\t' && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '"'
		&& input[i] != '\'' && input[i] != '\n')
		i++;
	tok = add_token(head, (t_token_data){TOKEN_WORD, &input[start],
			i - start, has_space});
	if (!tok)
		return (-1);
	tok->quoted = 0;
	return (i);
}
char	*my_getenv_len(char *name, size_t len, char **envp)
{
	size_t	i;

	i = 0;
	if (!name || !envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp_lap(envp[i], name, len) == 0
			&& envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
