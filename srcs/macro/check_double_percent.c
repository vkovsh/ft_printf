#include "ft_printf.h"

void		check_double_percent(char *format)
{
    while ((format = ft_strstr(format, "\045\045")))
        *(format + 1) = '\033';
}
