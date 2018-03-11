/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:23:32 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/11 18:39:02 by vkovsh           ###   ########.fr       */
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
        else if (*(bytes[b_counter]))
        {
			//printf("{%c}", sp.spec.next_char);
            sp.value = init_min_str(sp.spec.next_char);
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
        }
        else if (sp.spec.next_char == '%' /*&& (bytes[b_counter + 1])*/)
        {
			//printf("{%c}", sp.spec.next_char);
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
/*
void            parse_specs(char *format, t_list **parsed_values)
{
    char		**bytes;
    int			b_counter;
    t_value		sp;
    size_t		len;
    char        *first_spec_pos;

    check_double_percent(format);
    b_counter = 0;
    first_spec_pos = check_first_inclusion(parsed_values, format);
    bytes = ft_strsplit(first_spec_pos, '%');
    while (bytes[b_counter])
    {
        //char *tmp = bytes[b_counter];
        sp.spec = get_spec(&bytes[b_counter]);
        if (sp.spec.type != none)
        {
            sp.value = NULL;
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
        }
        else if (*(bytes[b_counter]))
        {
            sp.value = init_min_str(sp.spec.next_char);
            //write(1, &(sp.spec.next_char), 1);
            sp.spec.type = none;
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
            //bytes[b_counter] = ft_strjoin("%", tmp);
        }
        if (*(bytes[b_counter]))
        {
            sp.spec.type = T;
            sp.spec.asterisk_width = FALSE;
            sp.spec.asterisk_precision = FALSE;
            sp.spec.asterisk_color = FALSE;
            sp.spec.asterisk_background = FALSE;
            sp.spec.width = 0;
            sp.spec.precision = 1;
            len = ft_strlen((char *) (bytes[b_counter]));
            sp.value = ft_memalloc(len);
            ft_memmove(sp.value, (char *) (bytes[b_counter]), len);
            ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
        }
        b_counter++;
    }
}
*/
