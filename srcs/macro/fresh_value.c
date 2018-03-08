#include "ft_printf.h"

t_value     *fresh_value(t_type t, void *data, size_t count)
{
    t_value *sp;

    if (!(sp = (t_value *)malloc(sizeof(t_value))))
        return (NULL);
    sp->spec.type = t;
    if (!data)
        sp->value = NULL;
    else
    {
        sp->value = ft_strnew(count);
        ft_memmove(sp->value, data, count);
    }
    sp->spec.asterisk_width = FALSE;
    sp->spec.asterisk_precision = FALSE;
    sp->spec.asterisk_color = FALSE;
    sp->spec.asterisk_background = FALSE;
    sp->spec.width = 0;
    sp->spec.precision = 1;
    return (sp);
}
