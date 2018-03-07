#include "ft_printf.h"

int             ft_dprintf(int fd, const char *format, ...)
{
    t_pfargs    pf;

    if (!ft_strchr(format, '%'))
        return (ft_output(fd, format, &(pf.length)));
    init_list(format, &(pf.t), &(pf.output));
    va_start(pf.argptr, format);
    while (pf.t)
    {
        set_spec(&pf);
        check_asterisk(&pf);
        set_value(&pf);
        pf.t = (pf.t)->next;
    }
    va_end(pf.argptr);
    ft_output(fd, pf.output, &(pf.length));
    ft_strdel(&(pf.output));
    ft_lstdel(&(pf.t), &del_one);
    return (pf.length);
}
