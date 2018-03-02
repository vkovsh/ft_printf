#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <locale.h>

int		main(void)
{
	ft_printf("example: %p\n", &ft_printf);
	printf("example: %p\n", &ft_printf);
	return (0);
}