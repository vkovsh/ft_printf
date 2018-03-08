#include "ft_printf.h"

char			*init_min_str(int c)
{
    char		*min_str;

    min_str = ft_strnew(1);
    min_str[0] = c;
    return (min_str);
}