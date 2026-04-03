/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:35:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/30 15:07:07 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

// -------------------------ft_replace --------------------

char	*ft_replace(char *str, const char *old, const char *new)
{
	char	*pos;
	char	*result;
	size_t	len_before;
	size_t	len_after;

	pos = ft_strstr_lap(str, old);
	if (!pos)
		return (str);
	len_before = pos - str;
	len_after = ft_strlen_lap(pos + ft_strlen_lap(old));
	result = malloc(len_before + ft_strlen_lap(new) + len_after + 1);
	if (!result)
		return (NULL);
	ft_memcpy_lap(result, str, len_before);
	ft_memcpy_lap(result + len_before, new, ft_strlen_lap(new));
	ft_memcpy_lap(result + len_before + ft_strlen_lap(new), pos
		+ ft_strlen_lap(old), len_after);
	result[len_before + ft_strlen_lap(new) + len_after] = '\0';
	free(str);
	return (result);
}

// ------------------------------- ft_substr -----------------------

char	*ft_substr_lap(const char *line, int start, int len)
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

// ------------------------------- ft_memcpy -----------------------
void	*ft_memcpy_lap(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
	{
		*d = *s;
		s++;
		d++;
	}
	return (dest);
}

// --------------------------- ft_strncpy ----------------------------
char	*ft_strncpy_lap(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// ------------------------ ft_strncmp ----------------------------------

int	ft_strncmp_lap(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
