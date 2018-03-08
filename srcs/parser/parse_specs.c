#include "ft_printf.h"

void		    parse_specs(char *format, t_list **parsed_values)
{
    char		**bytes;
    int			b_counter;
    t_value		*sp;
    size_t		len;
    char		*first_spec_pos;

    check_double_percent(format);
    b_counter = 0;
    first_spec_pos = ft_strchr(format, '%');
    int diff = first_spec_pos - format;
    if (diff)
    {
        sp = fresh_value(T, format, diff);
        ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
        free(sp);
    }
    bytes = ft_strsplit(first_spec_pos, '%');
    while (bytes[b_counter])
    {
        char *tmp = bytes[b_counter];

        sp = (t_value *)malloc(sizeof(t_value));
        sp->spec = get_spec(&bytes[b_counter]);
        if (sp->spec.type != none)
        {
            sp->value = NULL;
            ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
            free(sp);
        }
        else
        {
            bytes[b_counter] = ft_strjoin("%", tmp);
        }
        if (*(bytes[b_counter]))
        {
            sp = (t_value *)malloc(sizeof(t_value));
            sp->spec.type = T;
            sp->spec.asterisk_width = FALSE;
            sp->spec.asterisk_precision = FALSE;
            sp->spec.asterisk_color = FALSE;
            sp->spec.asterisk_background = FALSE;
            sp->spec.width = 0;
            sp->spec.precision = 1;
            len = ft_strlen((char *)(bytes[b_counter]));
            sp->value = ft_memalloc(len);
            ft_memmove(sp->value, (char *)(bytes[b_counter]), len);
            ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
            free(sp);
        }
        b_counter++;
    }
}
