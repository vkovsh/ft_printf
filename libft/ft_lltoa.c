#include <stdlib.h>
#include "libft.h"

static int 	ft_lllen(long long n)
{
	int		len;

	len = 2;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n /= 10)
		len++;
	return (len);
}

char		*ft_lltoa(long long n)
{
	int		len;
	char	*res;
	int		check;

	if (n == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	len = ft_lllen(n);
	check = 0;
	if (n < 0)
	{
		n *= -1;
		check = 1;
	}
	if ((res = (char *)malloc(len)) == NULL)
		return (NULL);
	res[--len] = '\0';
	if (check)
		res[0] = '-';
	res[--len] = n % 10 + 48;
	while (n /= 10)
		res[--len] = n % 10 + 48;
	return (res);
}
