/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:23:32 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 14:37:31 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*check_first_inclusion(t_list **parsed_values,
		char *format)
{
	char		*first_spec_pos;
	t_value		sp;
	int			diff;

	first_spec_pos = ft_strchr(format, '%');
	diff = first_spec_pos - format;
	if (diff)
	{
		sp = fresh_value(T, format, diff);
		ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
	}
	return (first_spec_pos);
}

static t_spec	get_safe_spec(char **spec_str)
{
	t_spec		spec;
	char		*to_del;
	char		*new_spec_str;
	size_t		length;

	to_del = *spec_str;
	spec = get_spec(spec_str);
	if (to_del != (*spec_str))
	{
		length = ft_strlen(*spec_str);
		new_spec_str = ft_strnew(length);
		ft_memmove(new_spec_str, *spec_str, length);
		ft_strdel(&to_del);
		*spec_str = new_spec_str;
	}
	return (spec);
}

static void		safe_add_to_list(t_value sp,
		t_list **parsed_values,
		char *spec_txt)
{
	if (sp.spec.type != none)
	{
		sp.value = NULL;
		ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
	}
	else
	{
		sp.value = init_min_str(sp.spec.next_char);
		ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
	}
	if (*spec_txt)
	{
		sp = fresh_value(T, spec_txt, ft_strlen(spec_txt));
		ft_lstadd(parsed_values, ft_lstnew(&sp, sizeof(t_value)));
	}
}

static void		delete_array(char **bytes)
{
	int 		i;

	i = -1;
	while (bytes[++i])
		ft_strdel(&(bytes[i]));
	*bytes = NULL;
	free(bytes);
}

void			parse_specs(char *format,
		t_list **parsed_values)
{
	char		**bytes;
	int			b_counter;
	t_value		sp;

	check_double_percent(format);
	b_counter = -1;
	format = check_first_inclusion(parsed_values, format);
	bytes = ft_strsplit(format, '%');
	while (bytes[++b_counter])
	{
		sp.spec = get_safe_spec(&bytes[b_counter]);
		safe_add_to_list(sp, parsed_values, bytes[b_counter]);
	}
	delete_array(bytes);
}
