/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:57:37 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/06 11:58:21 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_ulllen(unsigned long long int n, int base)
{
	int				length;

	length = 1;
	while ((n /= base))
		length++;
	return (length);
}

char				*ft_ulltoa_base(unsigned long long int n, int base)
{
	char			*str;
	int				length;

	str = ft_strnew((length = ft_ulllen(n, base)));
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
