/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:11:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/06 17:35:51 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
/*
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
        sp = fresh_value(T, format, diff);
		ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
		free(sp);
	}
	bytes = ft_strsplit(first_spec_pos, '%');
	while (bytes[b_counter])
	{
		char *tmp = bytes[b_counter];

		sp = (t_value *)malloc(sizeof(t_value));
		sp->spec = get_spec(&bytes[b_counter]);
		if (sp->spec.type != none)
		{
			sp->value = NULL;
			ft_lstadd(parsed_values, ft_lstnew(sp, sizeof(t_value)));
			free(sp);
		}
		else
		{
			bytes[b_counter] = ft_strjoin("%", tmp);
		}
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
*/
void			check_asterisk(t_pfargs *pf)
{
	int 		color_nbr;
	t_color		color;

	pf->spec.width = (pf->spec.asterisk_width) ?
	va_arg(pf->argptr, int) : pf->spec.width;
	pf->spec.precision = (pf->spec.asterisk_precision) ?
	va_arg(pf->argptr, int) : pf->spec.precision;
	if (pf->spec.asterisk_background)
	{
		color_nbr = va_arg(pf->argptr, int);
		color.r = (unsigned char)(color_nbr >> 16);
		color.g = (unsigned char)((color_nbr << 16) >> 24);
		color.b = (unsigned char)color_nbr;
		pf->spec.background = color;
	}
	if (pf->spec.asterisk_color)
	{
		color_nbr = va_arg(pf->argptr, int);
		color.r = (unsigned char)(color_nbr >> 16);
		color.g = (unsigned char)((color_nbr << 16) >> 24);
		color.b = (unsigned char)color_nbr;
		pf->spec.color = color;
	}
}

void			set_spec(t_pfargs *pf)
{
	pf->spec = ((t_value *)((pf->t)->content))->spec;
}

void			set_value(t_pfargs *pf)
{
	if (pf->spec.type == T)
	{
		join_value(&(pf->output), ((t_value *)((pf->t)->content))->value, pf->spec);
	}
	else if (pf->spec.type == r)
	{
		unsigned char *np = va_arg(pf->argptr, unsigned char *);
		char *octal = ft_strnew(0);
		while (*np)
		{
			char *a = ft_ulltoa_base(*np, 8);
			if (ft_strlen(a) == 2)
				a = ft_strjoin("0", a);
			else if (ft_strlen(a) == 1)
				a = ft_strjoin("00", a);
			char *nbr = ft_strjoin("\134", a);
            octal = ft_strjoin(octal, nbr);
			np++;
		}
		octal = ft_strjoin(octal, "\134000");
        join_value(&(pf->output), octal, pf->spec);
	}
	else if (pf->spec.type == S || (pf->spec.type == s && pf->spec.flag2 == l))
		join_value(&(pf->output), ft_wstr_to_str(va_arg(pf->argptr, wchar_t *)), pf->spec);
	else if (pf->spec.type == C || (pf->spec.type == c && pf->spec.flag2 == l))
	{
		wchar_t wc = va_arg(pf->argptr, wchar_t);
        wchar_t *wstr = (wchar_t *)malloc(sizeof(wchar_t) * 2);
        wstr[0] = wc;
        wstr[1] = 0;
		join_value(&(pf->output), ft_wstr_to_str(wstr), pf->spec);
	}
	else if (pf->spec.type == d || pf->spec.type == i || pf->spec.type == D)
		set_signed_decimal(pf);
	else if (pf->spec.type == u || pf->spec.type == U || pf->spec.type == x ||
		pf->spec.type == X || pf->spec.type == o || pf->spec.type == O ||
		pf->spec.type == B || pf->spec.type == b)
	{
		set_unsigned_value(pf);
	}
	else if (pf->spec.type == c)
		join_value(&(pf->output), init_min_str(va_arg(pf->argptr, int)), pf->spec);
	else if (pf->spec.type == s)
	{
		char *res = va_arg(pf->argptr, char *);
		if (!res)
			res = ft_strdup("(null)");
		join_value(&(pf->output), res, pf->spec);
	}
	else if (pf->spec.type == PERCENT)
		pf->output = ft_strjoin(pf->output, "\045");
	else if (pf->spec.type == p)
		join_value(&(pf->output), ft_strjoin("0x", ft_strtolower(ft_ulltoa_base(va_arg(pf->argptr, unsigned long long), 16))), pf->spec);
}

void            del_one(void *content, size_t content_size)
{
    if (content != NULL && content_size != 0)
        free(content);
}

int				ft_printf(const char *format, ...)
{
	t_pfargs	pf;

	if (!ft_strchr(format, '%'))
		return (ft_output(1, format, &(pf.length)));
	init_list(format, &(pf.t), &(pf.output));
	va_start(pf.argptr, format);
	while (pf.t)
	{
		set_spec(&pf);
		check_asterisk(&pf);
		/*printf("back: %x%x%x asterisk: %d rgb: %x%x%x asterisk: %d f1: %d %d %d %d %d   %d %d, w: %d, p: %d, f2: %d t: %c\n",
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
	ft_output(1, pf.output, &(pf.length));
    ft_strdel(&(pf.output));
    ft_lstdel(&(pf.t), &del_one);
	return (pf.length);
}
