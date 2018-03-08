#include "ft_printf.h"

void			init_list(const char *format, t_list **t, char **output)
{
    char *format_cpy;

    format_cpy = ft_strnew(ft_strlen(format));
    ft_memmove(format_cpy, format, ft_strlen(format));
    *t = NULL;
    *output = ft_strnew(0);
    parse_specs(format_cpy, t);
    ft_lstrev(t);
}
