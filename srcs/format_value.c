/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:24:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/06 16:41:36 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

static void	set_width(char **value, t_spec spec)
{
	char	*spaces;
	int		length;

	if (spec.width)
	{
		length = (int)ft_strlen(*value);
		if (spec.width > length)
		{
			spaces = ft_strnew(spec.width - length);
			if (spec.minus_flag == FALSE && spec.zero_flag == TRUE && spec.precision < length)
				ft_memset(spaces, '0', spec.width - length);
            else
			    ft_memset(spaces, ' ', spec.width - length);
			if (spec.minus_flag == TRUE)
			{
				*value = ft_strjoin(*value, spaces);
			}
                /*
			else if (spec.plus_flag && spec.zero_flag)
			{
				*value = ft_strjoin(ft_strjoin("+", spaces), (*value) + 1);
			}*/
			else
			{
				*value = ft_strjoin(spaces, *value);
			}
		}
	}
}

static void	set_sharp(char **value, t_spec spec)
{
	if (spec.sharp_flag == TRUE)
	{
		if (spec.type == x || spec.type == X ||
			spec.type == b || spec.type == o)
		{
			if (spec.type == x)
				*value = ft_strjoin("0x", *value);
			else if (spec.type == X)
				*value = ft_strjoin("0X", *value);
			else if (spec.precision < (int)ft_strlen(*value))
				*value = ft_strjoin("0", *value);
		}
	}
}

t_bool			is_numeric_type(t_type t)
{
	if (t == i || t == d ||
		t == u || t == U ||
		t == o || t == O ||
		t == x || t == X ||
		t == b || t == B)
		return (TRUE);
	return (FALSE);
}

static void	set_precision(char **value, t_spec spec)
{
	char	*zeros;
	int		length;

	if (is_numeric_type(spec.type))
	{
		if (spec.precision)
		{
			length = (int)ft_strlen(*value);
			if (spec.precision > length)
			{
				zeros = ft_strnew(spec.precision - length);
				ft_memset(zeros, '0', spec.precision - length);
				*value = ft_strjoin(zeros, *value);
			}
		}
	}
	else if (spec.type == s)
	{
		if (spec.precision > 0)
		{
			if (spec.precision < (int)ft_strlen(*value))
			{
				char *h = ft_strnew(spec.precision);
				ft_memmove(h, *value, spec.precision);
				*value = h;
			}
		}
	}
}

void			set_color_and_background(char **value, t_spec spec)
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

void			set_plus_and_space(char **value, t_spec spec)
{
	if (is_numeric_type(spec.type))
	{
		if (spec.plus_flag)
		{
			if (**value != '-')
				*value = ft_strjoin("+", *value);
		}
		else if (spec.space_flag)
			*value = ft_strjoin("\40", *value);
	}	
}

void			join_value(char **output, char *value, t_spec spec)
{
	if (spec.type != T)
	{
		set_plus_and_space(&value, spec);
		set_precision(&value, spec);
		set_sharp(&value, spec);
		set_color_and_background(&value, spec);
		set_width(&value, spec);
	}
	*output = ft_strjoin(*output, value);
}
