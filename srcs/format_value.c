/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:24:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/02 02:25:10 by vkovsh           ###   ########.fr       */
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
			ft_memset(spaces, ' ', spec.width - length);
			if (spec.minus_flag == TRUE)
				*value = ft_strjoin(*value, spaces);
			else
				*value = ft_strjoin(spaces, *value);
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
		t == u || t == o ||
		t == x || t == X ||
		t == b)
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

static void		set_color(char **value, t_spec spec)
{
	char 		*color;

	if (spec.color.r || spec.color.g || spec.color.b)
	{
		color = ft_strjoin("\x1b[38;2;", ft_strjoin(ft_itoa(spec.color.r), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.g), ";"));
		color = ft_strjoin(color, ft_strjoin(ft_itoa(spec.color.b), "m"));
		*value = ft_strjoin(color, *value);
		*value = ft_strjoin(*value, "\x1b[0m");
	}
}

void		join_value(char **output, char *value, t_spec spec)
{
	if (spec.type != T)
	{
		set_precision(&value, spec);
		set_sharp(&value, spec);
		set_color(&value, spec);
		set_width(&value, spec);
	}
	*output = ft_strjoin(*output, value);
}
