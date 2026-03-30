/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:34:04 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/30 15:03:54 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lap.h"

// ------------------ ft_strlen ------------------
int	ft_strlen_lap(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// ------------------ ft_strcpy ------------------
char	*ft_strcpy_lap(char *dest, const char *src)
{
	char	*ptr;

	if (!dest || !src)
		return (dest);
	ptr = dest;
	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

// ------------------ ft_strcat ------------------
char	*ft_strcat_lap(char *dest, const char *src)
{
	char	*ptr;

	if (!dest || !src)
		return (dest);
	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

// ------------------ ft_strdup ------------------
char	*ft_strdup_lap(const char *s)
{
	size_t	len;
	char	*copy;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_strcpy_lap(copy, s);
	return (copy);
}

// ------------------ ft_strndup ------------------

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	size_t	i;
	char	*copy;

	if (!s)
		return (NULL);
	len = 0;
	while (len < n && s[len])
		len++;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
