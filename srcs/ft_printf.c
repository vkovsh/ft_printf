/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:11:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/02 04:54:25 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void		check_double_percent(char *format)
{
	while ((format = ft_strstr(format, "\045\045")))
		*(format + 1) = '\033';
}
	
static void		parse_specs(char *format, t_list **parsed_values)
{
	char		**bytes;
	int			b_counter;
	t_value		*sp;
	size_t		len;
	char		*first_spec_pos;

	check_double_percent(format);
	b_counter = 0;
	first_spec_pos = ft_strchr(format, '%');
	int diff = first_spec_pos - format;
	if (diff)
	{
		sp = (t_value *)malloc(sizeof(t_value));
		sp->spec.type = T;
		sp->value = ft_memalloc(diff + 1);
		ft_memmove(sp->value, format, diff);
		ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
		free(sp);
	}
	bytes = ft_strsplit(first_spec_pos, '%');
	while (bytes[b_counter])
	{
		sp = (t_value *)malloc(sizeof(t_value));
		sp->spec = get_spec(&bytes[b_counter]);
		/*
		printf("rgb: %x %x %x asterisk: %d f1: %d %d %d %d %d %d %d, w: %d, p: %d, f2: %d t: %c\n",
			sp->spec.color.r,
			sp->spec.color.g,
			sp->spec.color.b,
			sp->spec.asterisk_color,
			sp->spec.sharp_flag,
			sp->spec.zero_flag,
			sp->spec.minus_flag,
			sp->spec.plus_flag,
			sp->spec.space_flag,
			sp->spec.asterisk_width,
			sp->spec.asterisk_precision,
			sp->spec.width,
			sp->spec.precision,
			sp->spec.flag2,
			sp->spec.type);
			*/
		sp->value = NULL;
		ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
		free(sp);
		if (*(bytes[b_counter]))
		{
			sp = (t_value *)malloc(sizeof(t_value));
			sp->spec.type = T;
			sp->spec.asterisk_width = FALSE;
			sp->spec.asterisk_precision = FALSE;
			sp->spec.asterisk_color = FALSE;
			sp->spec.asterisk_background = FALSE;
			sp->spec.width = 0;
			sp->spec.precision = 1;
			len = ft_strlen((char *)(bytes[b_counter]));
			sp->value = ft_memalloc(len);
			ft_memmove(sp->value, (char *)(bytes[b_counter]), len);
			ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
			free(sp);
		}
		b_counter++;
	}
}

int				ft_output(const char *output,
	int *const length)
{
	*length = ft_strlen(output);
	write(1, output, *length);
	return (*length);
}

char			*init_min_str(char c)
{
	char		*min_str;

	min_str = ft_strnew(1);
	min_str[0] = c;
	return (min_str);
}

void			init_list(const char *format, t_list **t, char **output)
{
	char *format_cpy;

	format_cpy = ft_strnew(ft_strlen(format));
	ft_memmove(format_cpy, format, ft_strlen(format));
	*t = NULL;
	*output = ft_strnew(0);
	parse_specs(format_cpy, t);
	ft_lstrev(t);
}

void			check_asterisk(t_pfargs *pf)
{
	int 		color_nbr;
	t_color		color;

	pf->spec.width = (pf->spec.asterisk_width) ?
	va_arg(pf->argptr, int) : pf->spec.width;
	pf->spec.precision = (pf->spec.asterisk_precision) ?
	va_arg(pf->argptr, int) : pf->spec.precision;
	if (pf->spec.asterisk_color)
	{
		color_nbr = va_arg(pf->argptr, int);
		color.r = (unsigned char)(color_nbr >> 16);
		color.g = (unsigned char)((color_nbr << 16) >> 24);
		color.b = (unsigned char)color_nbr;
		pf->spec.color = color;
	}
	if (pf->spec.asterisk_background)
	{
		color_nbr = va_arg(pf->argptr, int);
		color.r = (unsigned char)(color_nbr >> 16);
		color.g = (unsigned char)((color_nbr << 16) >> 24);
		color.b = (unsigned char)color_nbr;
		pf->spec.background = color;
	}

}

void			set_spec(t_pfargs *pf)
{
	pf->spec = ((t_value *)((pf->t)->content))->spec;
}

void					set_signed_decimal(t_pfargs *pf)
{
	long long int 		decimal;

	decimal = va_arg(pf->argptr, long long int);
	if (pf->spec.flag2 == IGNORE2 && pf->spec.type != D)
		join_value(&(pf->output), ft_lltoa((int)decimal), pf->spec);
	else if (pf->spec.flag2 == h)
		join_value(&(pf->output), ft_lltoa((short int)decimal), pf->spec);
	else if (pf->spec.flag2 == l)
		join_value(&(pf->output), ft_lltoa((long int)decimal), pf->spec);
	else if (pf->spec.flag2 == ll || pf->spec.type == D)
		join_value(&(pf->output), ft_lltoa(decimal), pf->spec);
}
/*
void 						set_unsigned_value(t_pfargs *pf)
{
	unsigned long long int 	uns_value;

	uns_value = va_arg(pf->argptr, unsigned long long int);
	if (pf->spec.flag2 == h)
	{
		uns_value = (unsigned short int)uns_value;
		if (pf->spec.type == u || pf->spec.type == U)
			join_value(&(pf->output), ft_itoa(uns_value), pf->spec);
		else if (pf->spec.type == o || pf->spec.type == O)
			join_value(&(pf->output), ft_lltoa_base(uns_value, 8), pf->spec);
		else if (pf->spec.type == b || pf->spec.type == B)
			join_value(&(pf->output), ft_lltoa_base(uns_value, 2), pf->spec);
		else if (pf->spec.type == x || pf->spec.type == X)
			join_value(&(pf->output), ft_lltoa_base(uns_value, 16), pf->spec);
	}
	else if (pf->)*/
	/*
	else (pf->)

	if (pf->spec.type == u)
	{

	}
	else if (pf->spec.type == U)
	{

	}*/
//}

void			set_value(t_pfargs *pf)
{
	if (pf->spec.type == T)
		join_value(&(pf->output), ((t_value *)((pf->t)->content))->value, pf->spec);
	else if (pf->spec.type == S)
		join_value(&(pf->output), ft_wstr_to_str(va_arg(pf->argptr, wchar_t *)), pf->spec);
	else if (pf->spec.type == C)
	{
		wchar_t wc = va_arg(pf->argptr, wchar_t);
		join_value(&(pf->output), ft_wstr_to_str(&wc), pf->spec);
	}
	else if (pf->spec.type == d || pf->spec.type == i || pf->spec.type == D)
	{
		set_signed_decimal(pf);
	}
	/*
	else if (pf->spec.type == u || pf->spec.type == U || pf->spec.type == x ||
		pf->spec.type == X || pf->spec.type == o || pf->spec.type == O ||
		pf->spec.type == B || pf->spec->type == b)
	{
		set_unsigned_value(pf);
	}*/
	else if (pf->spec.type == u)
		join_value(&(pf->output), ft_itoa(va_arg(pf->argptr, unsigned int)), pf->spec);
	else if (pf->spec.type == U)
		join_value(&(pf->output), ft_lltoa_base(va_arg(pf->argptr, unsigned long long), 10), pf->spec);
	else if (pf->spec.type == c)
		join_value(&(pf->output), init_min_str(va_arg(pf->argptr, int)), pf->spec);
	else if (pf->spec.type == s)
		join_value(&(pf->output), va_arg(pf->argptr, char *), pf->spec);
	else if (pf->spec.type == PERCENT)
		pf->output = ft_strjoin(pf->output, "\045");
	else if (pf->spec.type == X)
		join_value(&(pf->output), ft_lltoa_base(va_arg(pf->argptr, unsigned long long), 16), pf->spec);
	else if (pf->spec.type == x)
		join_value(&(pf->output), ft_strtolower(ft_lltoa_base((int)va_arg(pf->argptr, unsigned long long), 16)), pf->spec);
	else if (pf->spec.type == o)
		join_value(&(pf->output), ft_lltoa_base((int)va_arg(pf->argptr, unsigned long long), 8), pf->spec);
	else if (pf->spec.type == O)
		join_value(&(pf->output), ft_lltoa_base(va_arg(pf->argptr, unsigned long long), 8), pf->spec);
	else if (pf->spec.type == b)
		join_value(&(pf->output), ft_lltoa_base((int)va_arg(pf->argptr, unsigned long long), 2), pf->spec);
	else if (pf->spec.type == B)
		join_value(&(pf->output), ft_lltoa_base(va_arg(pf->argptr, unsigned long long), 2), pf->spec);
	else if (pf->spec.type == p)
		join_value(&(pf->output), ft_strjoin("0x", ft_strtolower(ft_lltoa_base(va_arg(pf->argptr, unsigned long long), 16))), pf->spec);
}

int				ft_printf(const char *format, ...)
{
	t_pfargs	pf;

	if (!ft_strchr(format, '%'))
		return (ft_output(format, &(pf.length)));
	init_list(format, &(pf.t), &(pf.output));
	va_start(pf.argptr, format);
	while (pf.t)
	{
		set_spec(&pf);
		check_asterisk(&pf);
		/*printf("back: %x%x%x asterisk: %d rgb: %x%x%x asterisk: %d f1: %d %d %d %d %d %d %d, w: %d, p: %d, f2: %d t: %c\n",
			pf.spec.background.r,
			pf.spec.background.g,
			pf.spec.background.b,
			pf.spec.asterisk_background,
			pf.spec.color.r,
			pf.spec.color.g,
			pf.spec.color.b,
			pf.spec.asterisk_color,
			pf.spec.sharp_flag,
			pf.spec.zero_flag,
			pf.spec.minus_flag,
			pf.spec.plus_flag,
			pf.spec.space_flag,
			pf.spec.asterisk_width,
			pf.spec.asterisk_precision,
			pf.spec.width,
			pf.spec.precision,
			pf.spec.flag2,
			pf.spec.type);*/
		set_value(&pf);
		pf.t = (pf.t)->next;
	}
	va_end(pf.argptr);
	ft_output(pf.output, &(pf.length));
	return (pf.length);
}
