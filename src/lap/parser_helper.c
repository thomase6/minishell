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

// expand_token_value rewrite
// 1. declare res and idx. res is gonna be the malloc'ed string that is gonna replace t->value AFTER expansion and idx is the index of t->value[&idx.i] 
// 2. initialize idx.i = 0 and idx.j = 0;
// 3. then we do a while loop on t->value[&idx.i] to look for $. any value that has $ and quoted != 1 means we need to check the env keys to see if it matches and if it does we need to expand it.
// 4. after a value has been marked for possible expansion we go through the possible cases. Either $? or $ followed a character that is not space.
// 5. we should malloc somewhere before the if statements because the answer of the if statements will be saved inside of res.
// 5  if $? we have to expand this to the exit code that was previously used aka the exit code that is stored in t_shell *shell->last_status.
// 6. else if $ followed by any character that is not space we attempt to expand it to the key that is in the envp and if we are not successful we return an empty line. tmp = ""
// 7. after the expansion we have to save res to the t->value we can return 0.
  
static int	ft_intlen(int n)
{
	int	len;
	long	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	fill_expanded(char *res, char *val, t_shell *shell)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	size_t	start;
	size_t	var_len;

	i = 0;
	j = 0;
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] == '?')
		{
			tmp = ft_itoa_lap(shell->last_status);
			j += ft_strlen_lap(ft_strcpy_lap(res + j, tmp));
			free(tmp);
			i += 2;
		}
		else if (val[i] == '$'
			&& (ft_isalnum_lap(val[i + 1]) || val[i + 1] == '_'))
		{
			start = i + 1;
			var_len = 0;
			while (val[start + var_len]
				&& (ft_isalnum_lap(val[start + var_len])
					|| val[start + var_len] == '_'))
				var_len++;

			tmp = my_getenv_len(&val[start], var_len, shell->env);
			if (!tmp)
				tmp = "";

			j += ft_strlen_lap(ft_strcpy_lap(res + j, tmp));
			i = start + var_len;
		}
		else
			res[j++] = val[i++];
	}
	res[j] = '\0';
}

static size_t	get_expanded_len(char *val, t_shell *shell)
{
	size_t	i;
	size_t	len;
	char	*tmp;
	size_t	start;
	size_t	var_len;

	i = 0;
	len = 0;
	while (val[i])
	{
		if (val[i] == '$' && val[i + 1] == '?')
		{
			len += ft_intlen(shell->last_status);
			i += 2;
		}
		else if (val[i] == '$'
			&& (ft_isalnum_lap(val[i + 1]) || val[i + 1] == '_'))
		{
			start = i + 1;
			var_len = 0;
			while (val[start + var_len]
				&& (ft_isalnum_lap(val[start + var_len])))
				var_len++;

			tmp = my_getenv_len(&val[start], var_len, shell->env);
			if (tmp)
				len += ft_strlen_lap(tmp);
			i = start + var_len;
		}
		else
			len++, i++;
	}
	return (len);
}

int	expand_token_value(t_token *t, t_shell *shell)
{
	char	*res;
	size_t	len;

	if (!t || !t->value || t->quoted == 1)
		return (0);
	len = get_expanded_len(t->value, shell);
	res = malloc(len + 1);
	if (!res)
		return (-1);
	fill_expanded(res, t->value, shell);
	free(t->value);
	t->value = res;
	return (0);
}

int	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (expand_token_value(tmp, shell) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

