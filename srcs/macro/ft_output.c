#include "ft_printf.h"

int				ft_output(const int fd, const char *output, int *const length)
{
    *length = ft_strlen(output);
    write(fd, output, *length);
    return (*length);
}