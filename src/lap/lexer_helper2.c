/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:56:27 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/22 12:25:59 by stbagdah         ###   ########.fr       */
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

int	scan_word(t_shell *shell, t_scan_ctx *cntx, int i)
{
	int		start;
	t_token	*tok;

	(void)shell;
	start = i;
	while (cntx->input[i] && cntx->input[i] != ' ' && cntx->input[i] != '\t'
		&& cntx->input[i] != '|' && cntx->input[i] != '<'
		&& cntx->input[i] != '>' && cntx->input[i] != '"'
		&& cntx->input[i] != '\'' && cntx->input[i] != '\n')
		i++;
	tok = add_token(cntx->head,
			(t_token_data){TOKEN_WORD, &cntx->input[start],
			i - start, cntx->has_space});
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
