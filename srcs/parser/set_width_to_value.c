/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_width_to_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:01:04 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/16 18:01:08 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline void	set_width_to_null_string(char **value, t_spec spec)
{
	char			*spaces;
	int				length;

	length = spec.width;
	spaces = ft_strnew(length);
	ft_strdel(&(*value));
	if (spec.zero_flag)
	{
		ft_memset(spaces, '0', length);
		*value = spaces;
	}
	else
	{
		ft_memset(spaces, ' ', length);
		*value = spaces;
	}
}

static inline void	set_width_to_zero_pointer(char **value, t_spec spec)
{
	char			*spaces;
	int				length;
	char			*to_del;

	length = (int)ft_strlen(*value);
	spaces = ft_strnew(spec.width - length);
	to_del = spaces;
	ft_memset(spaces, '0', spec.width - length);
	spaces = ft_strjoin("0x", spaces);
	ft_strdel(&to_del);
	to_del = *value;
	*value = ft_strjoin(spaces, *value + 2);
	ft_strdel(&to_del);
	ft_strdel(&spaces);
}

void				set_width_to_value(char **value, t_spec spec)
{
	char			*spaces;
	int				length;
	char			*to_del;
	char			*to_del2;
	char			*double_str;

	to_del = NULL;
	if ((spec.type == s || spec.type == S) && spec.width && spec.precision == 0)
		set_width_to_null_string(value, spec);
	else if (spec.width)
	{
		length = (int)ft_strlen(*value);
		if (spec.width > length)
		{
			if (spec.type == p && spec.zero_flag)
				set_width_to_zero_pointer(value, spec);
			else
			{
				spaces = ft_strnew(spec.width - length);
				if (spec.minus_flag == FALSE && spec.zero_flag == TRUE && spec.precision < length)
					ft_memset(spaces, '0', spec.width - length);
            	else
			    	ft_memset(spaces, ' ', spec.width - length);
				to_del = *value;
				if (spec.minus_flag == TRUE)
                	*value = ft_strjoin(*value, spaces);
				else if ((spec.plus_flag || **value == '-') && spec.zero_flag)
				{
					to_del2 = spaces;
					if (**value != '-')
						spaces = ft_strjoin("+", spaces);
					else
						spaces = ft_strjoin("-", spaces);
					*value = ft_strjoin(spaces, (*value) + 1);
					ft_strdel(&to_del2);
				}
				else if (spec.sharp_flag == TRUE && spec.zero_flag == TRUE)
				{
					ft_memset(spaces, '0', spec.width - length);
					double_str = ft_strnew(2);
					double_str[0] = (*value)[0];
					double_str[1] = (*value)[1];
					to_del2 = spaces;
					spaces = ft_strjoin(double_str, spaces);
					*value = ft_strjoin(spaces, (*value) + 2);
					ft_strdel(&double_str);
					ft_strdel(&to_del2);
				}
				else
				{
					*value = ft_strjoin(spaces, *value);
				}
				ft_strdel(&to_del);
				ft_strdel(&spaces);
			}
		}
	}
}