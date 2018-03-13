/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:24:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/13 17:31:09 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

static void	set_width(char **value, t_spec spec)
{
	char	*spaces;
	int		length;

	if ((spec.type == s || spec.type == S) && spec.width && spec.precision == 0)
	{
		length = spec.width;
		spaces = ft_strnew(length);
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
		return ;
	}
	if (spec.width)
	{
		length = (int)ft_strlen(*value);
		if (spec.width > length)
		{
			spaces = ft_strnew(spec.width - length);
			if (spec.type == p && spec.zero_flag)
			{
				ft_memset(spaces, '0', spec.width - length);
				*value = ft_strjoin(ft_strjoin("0x", spaces), *value + 2);
				return ;
			}
			if (spec.minus_flag == FALSE && spec.zero_flag == TRUE && spec.precision < length)
				ft_memset(spaces, '0', spec.width - length);
            else
			    ft_memset(spaces, ' ', spec.width - length);
			if (spec.minus_flag == TRUE)
            {
                *value = ft_strjoin(*value, spaces);
            }
			else if ((spec.plus_flag || **value == '-') && spec.zero_flag)
			{
				if (**value != '-')
					*value = ft_strjoin(ft_strjoin("+", spaces), (*value) + 1);
				else
					*value = ft_strjoin(ft_strjoin("-", spaces), (*value) + 1);
			}
			else if (spec.sharp_flag == TRUE && spec.zero_flag == TRUE)
			{
				ft_memset(spaces, '0', spec.width - length);
				char *ln = ft_strnew(2);
				ln[0] = (*value)[0];
				ln[1] = (*value)[1];
				*value = ft_strjoin(ft_strjoin(ln, spaces), (*value) + 2);
				return ;
			}
			else
			{
				*value = ft_strjoin(spaces, *value);
			}
		}
	}
}

static void	set_sharp(char **value, t_spec spec)
{
	if (**value == '\000')
		return ;
	if (**value == 48 && !(*(*value + 1)))
		return ;
	if (spec.sharp_flag == TRUE)
	{
		if (spec.type == x || spec.type == X ||
                spec.type == b || spec.type == B ||
                spec.type == o || spec.type == O)
		{
			if (spec.type == x)
				*value = ft_strjoin("0x", *value);
			else if (spec.type == X)
				*value = ft_strjoin("0X", *value);
			else if (spec.precision < (int)ft_strlen(*value) && **value != 48)
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

t_bool			is_null_pointer(char *value)
{
	if (value[0] == '0' && value[1] == 'x' &&
			value[2] == '0' && value[3] == 0)
		return (TRUE);
	return (FALSE);
}

static void		set_precision(char **value, t_spec spec)
{
	char		*zeros;
	int			length;

	if (spec.type == p)
	{
		if (is_null_pointer(*value))
		{
			if (spec.precision >= 0)
			{
				*value = ft_strdup("0x");
				if (spec.precision >= 1)
				{
					char *zeros = ft_strnew(spec.precision);
					ft_memset(zeros, '0', spec.precision);
					*value = ft_strjoin(*value, zeros);
				}
				return ;
			}
		}
		else
		{
			int p_len = (int)ft_strlen((*value + 2));
			if (p_len < spec.precision)
			{
				char *zeros = ft_strnew(spec.precision - p_len);
				ft_memset(zeros, '0', spec.precision - p_len);
				*value = ft_strjoin(ft_strjoin("0x", zeros), *value + 2);
			}
			return ;
		}
	}
	if (is_numeric_type(spec.type))
	{
		if (spec.precision)
		{
			length = (int)ft_strlen(*value);
            if (spec.space_flag)
                length--;
			if (spec.precision > length)
			{
                zeros = ft_strnew(spec.precision - length);
                ft_memset(zeros, '0', spec.precision - length);
                if (spec.space_flag == FALSE || (spec.type != i && spec.type != d))
                {
					if (**value == '-')
						*value = ft_strjoin(ft_strjoin("-0", zeros), *value + 1);
					else if (**value == '+')
						*value = ft_strjoin(ft_strjoin("+0", zeros), *value + 1);
					else
						*value = ft_strjoin(zeros, *value);
                }
                else
                {
                    *value = ft_strjoin(ft_strjoin("\040", zeros), *value + 1);
                }
			}
			else if (spec.precision == length && **value == '+')
			{
				*value = ft_strjoin("+0", *value + 1);
			}
			else if (spec.precision == length && **value == '-')
			{
				*value = ft_strjoin("-0", *value + 1);
			}
		}
		else
		{
			if (spec.sharp_flag == FALSE)
			{
				int len = (int)ft_strlen(*value);
				if ((*value)[len - 1] == 48)
				{
					(*value)[len - 1] = '\000';
				}
			}
			else if (spec.sharp_flag == TRUE &&
					(spec.type == x || spec.type == X))
			{
				int len = (int)ft_strlen(*value);
				if ((*value)[len - 1] == 48)
				{
					(*value) = ft_strnew(0);
					spec.sharp_flag = FALSE;
				}
			}
		}
	}
	else if (spec.type == s || spec.type == S)
	{
		if (spec.precision > 0)
		{
			if (spec.type == s)
			{
				if (spec.precision < (int)ft_strlen(*value))
				{
					char *h = ft_strnew(spec.precision);
					ft_memmove(h, *value, spec.precision);
					*value = h;
				}
			}
			else
			{
				if (spec.precision < (int)ft_strlen(*value))
				{
					int k = (spec.precision / 3) * 3;
					if (!k)
						k = 1;
					char *h = ft_strnew(k);
					ft_memmove(h, *value, k);
					*value = h;
				}

			}
		}
		else if (spec.precision == 0 && spec.asterisk_precision)
		{
			*value = ft_strnew(0);
		}
		else if (spec.precision == 0)
		{
			if (spec.type == s)
			{
				char *tmp = *value;
				if (tmp)
				{
					while (*tmp)
					{
						*tmp = ' ';
						tmp++;
					}
				}
			}
			else
			{
				*value = ft_strnew(0);
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
			{
				if (is_unsigned(spec.type) == FALSE)
				{
					*value = ft_strjoin("+", *value);
				}
			}
		}
		else if (spec.space_flag)
        {
            if (**value != '-')
			{	if (spec.type == d || spec.type == i)
				{
					*value = ft_strjoin("\40", *value);
				}
			}
        }
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
	*output = ft_strjoin(*output, value);
}
