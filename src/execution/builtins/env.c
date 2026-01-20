#include "../../../inc/execution.h"

int	builtin_env(char **envp) // CHANGE: add t_shell *shell
{
	int i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
