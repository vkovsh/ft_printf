/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:24:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 19:26:49 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_color_and_background_to_value(char **value, t_spec spec)
{
	char 		*color;

	if ((spec.color.r || spec.color.g || spec.color.b) &&
		(spec.background.r || spec.background.g || spec.background.b))
	{
		color = ft_strjoin("\x1b[38;2;", ft_strjoin(ft_itoa(spec.color.r), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.g), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.b), ";48;2;"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.background.r), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.background.g), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.background.b), "m"));
		*value = ft_strjoin(color, *value);
		*value = ft_strjoin(*value, "\x1b[0m");
	}
	else if (spec.color.r || spec.color.g || spec.color.b)
	{
		color = ft_strjoin("\x1b[38;2;", ft_strjoin(ft_itoa(spec.color.r), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.g), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.b), "m"));
		*value = ft_strjoin(color, *value);
		*value = ft_strjoin(*value, "\x1b[0m");
	}
	else if (spec.background.r || spec.background.g || spec.background.b)
	{
		color = ft_strjoin("\x1b[48;2;", ft_strjoin(ft_itoa(spec.background.r), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.background.g), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.background.b), "m"));
		*value = ft_strjoin(color, *value);
		*value = ft_strjoin(*value, "\x1b[0m");
	}
}

void			join_value(char **output, char *value, t_spec spec)
{
	char 		*to_del;

	if (spec.type != T)
	{
		set_plus_and_space_to_value(&value, spec);
		set_precision_to_value(&value, spec);
		set_sharp_to_value(&value, spec);
		set_color_and_background_to_value(&value, spec);
		set_width_to_value(&value, spec);
		if (spec.zero_flag && spec.space_flag)
		{
			char *first_space = ft_strchr(value, ' ');
			if (first_space)
			{
				*first_space = '0';
				*value = ' ';
			}
		}
	}
	to_del = *output;
	*output = ft_strjoin(*output, value);
	ft_strdel(&to_del);
}
