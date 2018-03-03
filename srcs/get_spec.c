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
			spec->precision = -1;
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
}

t_spec			get_spec(char **txt_pointer)
{
	t_spec		spec;

	set_flag1(txt_pointer, &spec);
	set_width(txt_pointer, &spec);
	set_precision(txt_pointer, &spec);
	set_flag2(txt_pointer, &spec);
	set_type(txt_pointer, &spec);
	return (spec);
}