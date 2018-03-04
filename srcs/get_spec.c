#include "ft_printf.h"

t_bool			is_flag1(char c)
{
	if (c == SHARP || c == ZERO ||
		c == MINUS || c == PLUS ||
		c == SPACE)
		return (TRUE);
	return (FALSE);
}

t_bool			is_type(char k)
{
	if (k == s || k == S || k == p || k == d ||
		k == D || k == i || k == o || k == O ||
		k == u || k == U || k == x || k == X ||
		k == c || k == C || k == T || k == b ||
		k == PERCENT)
		return (TRUE);
	return (FALSE);
}

void			set_flag1(char **txt_pointer, t_spec *spec)
{
	char		flag;

	spec->sharp_flag = FALSE;
	spec->zero_flag = FALSE;
	spec->minus_flag = FALSE;
	spec->plus_flag = FALSE;
	spec->space_flag = FALSE;
	spec->asterisk_width = FALSE;
	spec->asterisk_precision = FALSE;
	while (is_flag1(**txt_pointer))
	{
		flag = **txt_pointer;
		if (flag == SHARP)
			spec->sharp_flag = TRUE;
		else if (flag == ZERO)
			spec->zero_flag = TRUE;
		else if (flag == MINUS)
			spec->minus_flag = TRUE;
		else if (flag == PLUS)
			spec->plus_flag = TRUE;
		else
			spec->space_flag = TRUE;
		(*txt_pointer)++;
	}
}

void			set_width(char **txt_pointer, t_spec *spec)
{
	char		*str;
	int			check;
	char		*width;

	str = *txt_pointer;
	if (ft_isdigit(**txt_pointer))
	{
		str = *txt_pointer;
		check = 0;
		while (ft_isdigit(str[check]))
			check++;
		width = ft_strnew(check);
		ft_memmove(width, str, check);
		spec->width = ft_atoi(width);
		*(txt_pointer) += check;
	}
	else if (**txt_pointer == '*')
	{
		(*(txt_pointer))++;
		spec->width = 0;
		spec->asterisk_width = TRUE;
	}
	else
		spec->width = 0;
}

void			set_precision(char **txt_pointer, t_spec *spec)
{
	char		*str;
	int			check;
	char		*precision;

	str = *txt_pointer;
	if (str[0] == '.')
	{
		str++;
		if (ft_isdigit(str[0]))
		{
			check = 0;
			while (ft_isdigit(str[check]))
				check++;
			precision = ft_strnew(check);
			ft_memmove(precision, str, check);
			spec->precision = ft_atoi(precision);
			str += check;
		}
		else if (str[0] == '*')
		{
			str++;
			spec->precision = 1;
			spec->asterisk_precision = TRUE;
		}
		*txt_pointer = str;
	}
	else
		spec->precision = -1;
}

void			set_flag2(char **txt_pointer, t_spec *spec)
{
	char		*str;

	str = *txt_pointer;
	if (str[0] == 'h')
	{
		str++;
		if (str[0] == 'h')
		{
			spec->flag2 = hh;
			str++;
		}
		else
			spec->flag2 = h;
	}
	else if (str[0] == 'l')
	{
		str++;
		if (str[0] == 'l')
		{
			spec->flag2 = ll;
			str++;
		}
		else
			spec->flag2 = l;
	}
	else if (str[0] == 'j')
	{
		str++;
		spec->flag2 = j;
	}
	else if (str[0] == 'z')
	{
		str++;
		spec->flag2 = z;
	}
	else
		spec->flag2 = IGNORE2;
	*txt_pointer = str;
}

void			set_type(char **txt_pointer, t_spec *spec)
{
	if (is_type(**txt_pointer))
	{
		spec->type = **txt_pointer;
		(*txt_pointer)++;
	}
	else
	{
		spec->type = c;
		(*txt_pointer)++;
	}
}


void			set_color(char **txt_pointer, t_spec *spec)
{
	char 		*str;

	str = *txt_pointer;
	if (str[0] == '{' && ft_strlen(str) > 7 && str[7] == '}')
	{
		if (ft_ishex(str[1]) &&
			ft_ishex(str[2]) &&
			ft_ishex(str[3]) &&
			ft_ishex(str[4]) &&
			ft_ishex(str[5]) &&
			ft_ishex(str[6]))
		{
			spec->color.r = (str[1] <= '9') ? (str[1] - '0') * 16 : (str[1] - 87) * 16;
			spec->color.r += (str[2] <= '9') ? (str[2] - '0') : (str[2] - 87);
			spec->color.g = (str[3] <= '9') ? (str[3] - '0') * 16 : (str[3] - 87) * 16;
			spec->color.g += (str[4] <= '9') ? (str[4] - '0') : (str[4] - 87);
			spec->color.b = (str[5] <= '9') ? (str[5] - '0') * 16 : (str[5] - 87) * 16;
			spec->color.b += (str[6] <= '9') ? (str[6] - '0') : (str[6] - 87);
			(*txt_pointer) += 8;
		}
	}
	else if (str[0] == '{' && ft_strlen(str) > 2 && str[2] == '}' && str[1] == '*')
	{
		spec->asterisk_color = TRUE;
		spec->color.r = 0;
		spec->color.g = 0;
		spec->color.b = 0;
		*(txt_pointer) += 3;
	}
	else
	{
		spec->asterisk_color = FALSE;
		spec->color.r = 0;
		spec->color.g = 0;
		spec->color.b = 0;
	}
}

t_spec			get_spec(char **txt_pointer)
{
	t_spec		spec;

	set_color(txt_pointer, &spec);
	set_flag1(txt_pointer, &spec);
	set_width(txt_pointer, &spec);
	set_precision(txt_pointer, &spec);
	set_flag2(txt_pointer, &spec);
	set_type(txt_pointer, &spec);
	return (spec);
}
