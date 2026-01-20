#include "libft.h"

int	ft_atoll(const char *str)
{
	int			i;
	long long	sum;
	int			sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		sum = ((sum * 10) + (str[i] - 48));
		i++;
	}
	return (sum * sign);
}