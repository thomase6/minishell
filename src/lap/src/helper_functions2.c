/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:35:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/18 11:01:15 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -------------------------ft_replace --------------------

char	*ft_replace(char *str, const char *old, const char *new)
{
	char	*pos;
	char	*result;
	size_t	len_before;
	size_t	len_after;

	pos = ft_strstr(str, old);
	if (!pos)
		return (str);
	len_before = pos - str;
	len_after = strlen(pos + strlen(old));
	result = malloc(len_before + strlen(new) + len_after + 1);
	if (!result)
		return (NULL);
	memcpy(result, str, len_before);
	memcpy(result + len_before, new, strlen(new));
	memcpy(result + len_before + strlen(new), pos + strlen(old), len_after);
	result[len_before + strlen(new) + len_after] = '\0';
	free(str);
	return (result);
}

// ------------------------------- ft_substr -----------------------

char	*ft_substr(const char *line, int start, int len)
{
	char	*sub;
	int		i;

	if (!line || start < 0 || len < 0)
		return (NULL);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && line[start + i])
	{
		sub[i] = line[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
