#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <locale.h>

int		main(void)
{
	ft_printf("example: %#*.*X, %#*.*x, %#*.10o\n", 30, 10, 'z', 30, 10, 'z', 30, 'z');
	printf("example: %#*.*X, %#*.*x, %#*.10o\n", 30, 10, 'z', 30, 10, 'z', 30, 'z');
	return (0);
}