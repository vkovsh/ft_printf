#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <locale.h>

int		main(void)
{
	ft_printf("example: %20p\n", &ft_printf);
	printf("example: %20p\n", &ft_printf);
	return (0);
}