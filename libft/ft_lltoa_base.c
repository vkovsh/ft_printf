#include "libft.h"

static inline int	ft_lllen(unsigned long long n, int base)
{
	int				length;

	length = 1;
	while ((n /= base))
		length++;
	return (length);
}

char				*ft_lltoa_base(unsigned long long n, int base)
{
	char			*str;
	int				length;

	str = ft_strnew((length = ft_lllen(n, base)));
	if (!n)
		str[0] = '0';
	while (n)
	{
		if (base <= 10)
			str[--length] = n % base + '0';
		else
			str[--length] = (n % base < 10) ? n % base + '0' : n % base + 55;
		n /= base;
	}
	return (str);
}