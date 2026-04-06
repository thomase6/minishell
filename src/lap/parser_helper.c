/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:29:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/04/06 10:39:42 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

static char	*get_var_value(char *val, size_t *i)
{
	size_t	start;
	char	var[256];
	size_t	len;
	char	*tmp;

	start = *i + 1;
	while (ft_isalnum_lap(val[start]))
		start++;
	if (start == *i + 1)
		return (NULL);
	len = start - (*i + 1);
	if (len >= sizeof(var))
		len = sizeof(var) - 1;
	ft_strncpy_lap(var, val + *i + 1, len);
	var[len] = '\0';
	*i = start;
	tmp = getenv(var);
	if (!tmp)
		tmp = "";
	return (tmp);
}

static int	process_dollar(char *val, char *res, t_index *idx, int last_exit)
{
	char	*tmp;

	if (val[idx->i + 1] == '?')
	{
		if (handle_exit(res, &idx->j, last_exit) == -1)
			return (-1);
		idx->i += 2;
	}
	else
	{
		tmp = get_var_value(val, &idx->i);
		if (tmp)
			idx->j += ft_strlen_lap(ft_strcpy_lap(res + idx->j, tmp));
		else
			res[(idx->j)++] = val[idx->i];
	}
	return (0);
}

static int	handle_loop(char *val, char *res, t_index *idx, int last_exit)
{
	while (val[idx->i])
	{
		if (val[idx->i] == '$')
		{
			if (process_dollar(val, res, idx, last_exit) == -1)
				return (-1);
		}
		else
			res[idx->j++] = val[idx->i++];
	}
	return (0);
}

static int	expand_token_value(t_token *t, char **envp, int last_exit)
{
	char	*res;
	t_index	idx;

	(void)envp;
	if (!t || !t->value || t->quoted == 1)
		return (0);
	res = malloc(ft_strlen_lap(t->value) * 5 + 1);
	if (!res)
		return (-1);
	idx.i = 0;
	idx.j = 0;
	if (handle_loop(t->value, res, &idx, last_exit) == -1)
		return (free(res), -1);
	res[idx.j] = '\0';
	free(t->value);
	return (t->value = res, 0);
}

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
