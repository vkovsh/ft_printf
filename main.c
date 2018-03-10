#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ft_atoi(av[ac - 2]) == 0)
	{
		if (*av[ac - 1] == 'f')
		{
			ft_printf("This is a simple test.");
			ft_printf("This is a simple test.\nSecond sentence.\n");
			ft_printf("");
			ft_printf("\n");
		}
		else if (*av[ac - 1] == 'p')
		{
			printf("This is a simple test.");
			printf("This is a simple test.\nSecond sentence.\n");
			printf("");
			printf("\n");
		}
	}
	else if (ft_atoi(av[ac - 2]) == 5)
	{
		if (*av[ac - 1] == 'p')
		{
			printf("%%");
			printf("aa%%bb");
			printf("%%%%%%%%%%");
			printf(".%%.%%.%%.%%.%%.%%.%%.%%.");
			printf("%");
			printf("% Zoooo");
			printf("{%}");
			printf("{% %}");
		}
		else if (*av[ac - 1] == 'f')
		{
			ft_printf("%%");
			ft_printf("aa%%bb");
			ft_printf("%%%%%%%%%%");
			ft_printf(".%%.%%.%%.%%.%%.%%.%%.%%.");
			ft_printf("%");
			ft_printf("% Zoooo");
			ft_printf("{%}");
			ft_printf("{% %}");
		}
	}
	else if (ft_atoi(av[ac - 2]) == 7)
	{
		if (*av[ac - 1] == 'p')
		{
			printf("{%S}", NULL);
		}
		else if (*av[ac - 1] == 'f')
		{
			ft_printf("{%S}", NULL);
		}
	}
	else if (ft_atoi(av[ac - 2]) == 16)
	{
		if (*av[ac - 1] == 'p')
		{
			int k = printf("aaa%caaa", 0);
			printf("\n%d\n", k);
		}
		else if (*av[ac - 1] == 'f')
		{
			int k = ft_printf("aaa%caaa", 0);
			ft_printf("\n%d\n", k);
		}
	}
	else if (ft_atoi(av[ac - 2]) == 17)
	{
		if (*av[ac - 1] == 'p')
		{
			int k = printf("aaa%Caaa", 0);
			printf("\n%d\n", k);
		}
		else if (*av[ac - 1] == 'f')
		{
			int k = ft_printf("aaa%Caaa", 0);
			ft_printf("\n%d\n", k);
		}
	}
	else if (ft_atoi(av[ac - 2]) == 42)
	{
		if (*av[ac - 1] == 'f')
		{
			ft_printf("%hd%hd", (short int)0, (short int)42);
			ft_printf("%hd", SHRT_MAX);
			ft_printf("%hd", SHRT_MIN);
			ft_printf("%hi%hi", 0, 42);
			ft_printf("%hi", SHRT_MAX);
			ft_printf("%hi", SHRT_MIN);
			ft_printf("%hu, %hu", 0, USHRT_MAX);
			ft_printf("%ho, %ho", 0, USHRT_MAX);
			ft_printf("%hx, %hx", 0, USHRT_MAX);
			ft_printf("%hX, %hX", 0, USHRT_MAX);
			ft_printf("%hO, %hO", 0, USHRT_MAX);
			ft_printf("%hU, %hU", 0, USHRT_MAX);
			ft_printf("%hD, %hD", 0, USHRT_MAX);
		}
		else if (*av[ac - 1] == 'p')
		{
			printf("%hd%hd", (short int)0, (short int)42);
			printf("%hd", SHRT_MAX);
			printf("%hd", SHRT_MIN);
			printf("%hi%hi", 0, 42);
			printf("%hi", SHRT_MAX);
			printf("%hi", SHRT_MIN);
			printf("%hu, %hu", 0, USHRT_MAX);
			printf("%ho, %ho", 0, USHRT_MAX);
			printf("%hx, %hx", 0, USHRT_MAX);
			printf("%hX, %hX", 0, USHRT_MAX);
			printf("%hO, %hO", 0, USHRT_MAX);
			printf("%hU, %hU", 0, USHRT_MAX);
			printf("%hD, %hD", 0, USHRT_MAX);
		}
	}
	else if (ft_atoi(av[ac - 2]) == 43)
	{
		if (*av[ac - 1] == 'f')
		{
			ft_printf("%hhd%hhd", 1, 42);
			ft_printf("%hhd", CHAR_MAX);
			ft_printf("%hhd", CHAR_MAX + 42);
			ft_printf("%hhd", CHAR_MIN);
			ft_printf("%hhd", CHAR_MIN - 42);
			ft_printf("%hhi%hhi", 0, 42);
			ft_printf("%hhd", CHAR_MAX);
			ft_printf("%hhd", CHAR_MAX + 42);
			ft_printf("%hhi", CHAR_MIN);
			ft_printf("%hhi", CHAR_MIN - 42);
			ft_printf("%hhu, %hhu", 0, UCHAR_MAX);
			ft_printf("%hho, %hho", 0, UCHAR_MAX);
			ft_printf("%hhx, %hhx", 0, UCHAR_MAX);
			ft_printf("%hhX, %hhX", 0, UCHAR_MAX);
			ft_printf("%hhu, %hhu", 0, UCHAR_MAX + 42);
			ft_printf("%hho, %hho", 0, UCHAR_MAX + 42);
			ft_printf("%hhx, %hhx", 0, UCHAR_MAX + 42);
			ft_printf("%hhX, %hhX", 0, UCHAR_MAX + 42);
			ft_printf("%hhO, %hhO", 0, USHRT_MAX);
			ft_printf("%hhU, %hhU", 0, USHRT_MAX);
			ft_printf("%hhD, %hhD", 0, USHRT_MAX);
			ft_printf("%hhC, %hhC", 0, L'米');
			ft_printf("%hhS, %hhS", 0, L"米米");
		}
		else if (*av[ac - 1] == 'p')
		{
			printf("%hhd%hhd", 1, 42);
			printf("%hhd", CHAR_MAX);
			printf("%hhd", CHAR_MAX + 42);
			printf("%hhd", CHAR_MIN);
			printf("%hhd", CHAR_MIN - 42);
			printf("%hhi%hhi", 0, 42);
			printf("%hhd", CHAR_MAX);
			printf("%hhd", CHAR_MAX + 42);
			printf("%hhi", CHAR_MIN);
			printf("%hhi", CHAR_MIN - 42);
			printf("%hhu, %hhu", 0, UCHAR_MAX);
			printf("%hho, %hho", 0, UCHAR_MAX);
			printf("%hhx, %hhx", 0, UCHAR_MAX);
			printf("%hhX, %hhX", 0, UCHAR_MAX);
			printf("%hhu, %hhu", 0, UCHAR_MAX + 42);
			printf("%hho, %hho", 0, UCHAR_MAX + 42);
			printf("%hhx, %hhx", 0, UCHAR_MAX + 42);
			printf("%hhX, %hhX", 0, UCHAR_MAX + 42);
			printf("%hhO, %hhO", 0, USHRT_MAX);
			printf("%hhU, %hhU", 0, USHRT_MAX);
			printf("%hhD, %hhD", 0, USHRT_MAX);
			printf("%hhC, %hhC", 0, L'米');
			printf("%hhS, %hhS", 0, L"米米");
		}
	}
	else if (ft_atoi(av[ac - 2]) == 50)
	{
		if (*av[ac - 1] == 'p')
		{
			printf("{%10d}", 42);
			printf("{%4d}", 10000);
			printf("{%30d}", 10000);
			printf("{%10d}", -42);
			printf("{%3c}", 0);
			printf("{%5p}", 0);
			printf("{%-15p}", 0);
			printf("{%-13p}", &strlen);
			printf("{%-12p}", &strlen);
			printf("{%10R}");
			printf("{%30S}", L"我是一只猫。");
			printf("{%-30S}", L"我是一只猫。");
		}
		else if (*av[ac - 1] == 'f')
		{
			ft_printf("{%10d}", 42);
			ft_printf("{%4d}", 10000);
			ft_printf("{%30d}", 10000);
			ft_printf("{%10d}", -42);
			ft_printf("{%3c}", 0);
			ft_printf("{%5p}", 0);
			ft_printf("{%-15p}", 0);
			ft_printf("{%-13p}", &strlen);
			ft_printf("{%-12p}", &strlen);
			ft_printf("{%10R}");
			ft_printf("{%30S}", L"我是一只猫。");
			ft_printf("{%-30S}", L"我是一只猫。");
		}
	}
	return (0);
}
