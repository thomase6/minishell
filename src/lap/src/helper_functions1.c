/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:35:14 by stbagdah          #+#    #+#             */
/*   Updated: 2026/03/19 15:24:55 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ------------------ ft_strcmp ------------------
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (s1 - s2);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// ------------------ ft_strjoin ------------------
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*res;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcat(res, s2);
	return (res);
}

// ------------------ ft_itoa ------------------
static void	num_to_str(char *s, long num, int len)
{
	s[len] = '\0';
	while (len > 0)
	{
		s[--len] = (num % 10) + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	long	num;
	long	tmp;

	num = n;
	len = (num <= 0);
	if (num < 0)
		num = -num;
	tmp = num;
	while (tmp > 0)
	{
		len++;
		tmp /= 10;
	}
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	if (n < 0)
		ptr[0] = '-';
	else if (n == 0)
		ptr[0] = '0';
	num_to_str(ptr + (n < 0), num, len - (n < 0));
	return (ptr);
}
// ----------------------- ft_strstr ----------------------

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
