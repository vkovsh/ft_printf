/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:11:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/02/21 18:27:54 by vkovsh           ###   ########.fr       */
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
		printf("f1: %d %d %d %d %d %d %d, w: %d, p: %d, f2: %d t: %c\n",
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
			sp->spec.width = 0;
			sp->spec.precision = -1;
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

int				ft_printf(const char *format, ...)
{
	t_pfargs	pf;

	if (!ft_strchr(format, '%'))
		return (ft_output(format, &(pf.length)));
	init_list(format, &(pf.t), &(pf.output));
	va_start(pf.argptr, format);
	while (pf.t)
	{
		pf.spec = ((t_value *)((pf.t)->content))->spec;
		pf.spec.width = (pf.spec.asterisk_width) ? va_arg(pf.argptr, int) : pf.spec.width;
		pf.spec.precision = (pf.spec.asterisk_precision) ? va_arg(pf.argptr, int) : pf.spec.precision;
		if (pf.spec.type == T)
			join_value(&(pf.output), ((t_value *)((pf.t)->content))->value, pf.spec);
		else if (pf.spec.type == d || pf.spec.type == i)
			join_value(&(pf.output), ft_itoa(va_arg(pf.argptr, int)), pf.spec);
		else if (pf.spec.type == c)
			join_value(&(pf.output), init_min_str(va_arg(pf.argptr, int)), pf.spec);
		else if (pf.spec.type == s)
			join_value(&(pf.output), va_arg(pf.argptr, char *), pf.spec);
		else if (pf.spec.type == PERCENT)
			pf.output = ft_strjoin(pf.output, "\045");
		else if (pf.spec.type == X)
			join_value(&(pf.output), ft_lltoa_base(va_arg(pf.argptr, long long), 16), pf.spec);
		else if (pf.spec.type == x)
			join_value(&(pf.output), ft_strtolower(ft_lltoa_base(va_arg(pf.argptr, long long), 16)), pf.spec);
		else if (pf.spec.type == o)
			join_value(&(pf.output), ft_lltoa_base(va_arg(pf.argptr, long long), 8), pf.spec);
		else if (pf.spec.type == b)
			join_value(&(pf.output), ft_lltoa_base(va_arg(pf.argptr, long long), 2), pf.spec);
		pf.t = (pf.t)->next;
	}
	va_end(pf.argptr);
	ft_output(pf.output, &(pf.length));
	return (pf.length);
}
