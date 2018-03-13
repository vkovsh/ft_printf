/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:23:32 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/13 13:15:25 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../../includes/ft_printf.h"
#include <stdio.h>

static char     *check_first_inclusion(t_list **parsed_values, char *format)
{
    char        *first_spec_pos;
    t_value     sp;
    int         diff;

    first_spec_pos = ft_strchr(format, '%');
    diff = first_spec_pos - format;
    if (diff)
    {
        sp = fresh_value(T, format, diff);
        ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
    }
    return (first_spec_pos);
}

void            parse_specs(char *format, t_list **parsed_values)
{
    char		**bytes;
    int			b_counter;
    t_value		sp;
    char        *first_spec_pos;

    check_double_percent(format);
    b_counter = 0;
    first_spec_pos = check_first_inclusion(parsed_values, format);
    bytes = ft_strsplit(first_spec_pos, '%');
    while (bytes[b_counter])
    {
        sp.spec = get_spec(&bytes[b_counter]);
        if (sp.spec.type != none)
        {
            sp.value = NULL;
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
        }
        else if (*(bytes[b_counter]) || (sp.spec.next_char && sp.spec.next_char != '%'))
        {
            sp.value = init_min_str(sp.spec.next_char);
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
        }
        else if (sp.spec.next_char == '%')
        {
            sp.value = init_min_str('%');
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
            b_counter++;
        }
        if (bytes[b_counter])
        {
            if (*(bytes[b_counter]))
            {
                sp = fresh_value(T, bytes[b_counter], ft_strlen(bytes[b_counter]));
                ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
            }
        }
		else
			break ;
        b_counter++;
    }
}
