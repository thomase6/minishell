/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:59:53 by texenber          #+#    #+#             */
/*   Updated: 2026/01/21 16:04:12 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/execution.h"

//this function finds the key string in the env double pointer
int find_env_var(char **env, char *key)
{
	int	i;
	int	key_len;

	if (!env || !key)
		return(-1);
	key_len = 0;
	i = 0;
	while (key[key_len] && key[key_len] != '=')
		key_len++;
	while (env[i])
	{
		if((ft_strncmp(env[i], key, key_len) == 0) && env[i][key_len] == '=')
			return (i);	
		i++;
	}
	return (-1);
}

//this function changes the value of a string in the env double pointer at position i with the string var
int	update_env_var(char **env, int i, char *var)
{
	char	*new_str;

	new_str = ft_strdup(var);
	if (!new_str)
		return (-1);
	free(env[i]);
	env[i] = new_str;
	return (0);
}

char **add_env_var(char **env, char *var)
{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	while(env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[count] = ft_strdup(var);
	if (!new_env[count])
	{
		free(new_env);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	free(env);
	return (new_env);
}

// this is just for testing
void test(void)
{
    char **env = malloc(sizeof(char *) * 3);
    env[0] = ft_strdup("PATH=/usr/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = NULL;
    
    printf("Before:\n");
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    
    env = add_env_var(env, "NEWVAR=test");
    
    printf("\nAfter:\n");
    for (int i = 0; env[i]; i++)
        printf("  [%d] %s\n", i, env[i]);
    
    free_argv(env);
}