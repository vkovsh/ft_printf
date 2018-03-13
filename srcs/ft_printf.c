/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:11:18 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/13 17:52:05 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../includes/ft_printf.h"
#include <stdio.h>

void			check_asterisk(t_pfargs *pf)
{
	int 		color_nbr;
	t_color		color;

	if (pf->spec.width && pf->spec.asterisk_width)
	{
		va_arg(pf->argptr, void *);
	}
	else
	{
		pf->spec.width = (pf->spec.asterisk_width) ?
			va_arg(pf->argptr, int) : pf->spec.width;
	}
	if (pf->spec.width < 0)
	{
		pf->spec.width *= -1;
		pf->spec.minus_flag = TRUE;
	}
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

void			set_value(t_pfargs *pf)
{
	if (pf->spec.type == none)
    {
        pf->spec.type = c;
        join_value(&(pf->output), ((t_value *)((pf->t)->content))->value, pf->spec);
    }
    else if (pf->spec.type == n)
    {
        int *count = va_arg(pf->argptr, int *);
        *count = (int)ft_strlen(pf->output);
    }
	else if (pf->spec.type == T)
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
    {
        wchar_t *wc = va_arg(pf->argptr, wchar_t * );
        if (wc)
        {
            join_value(&(pf->output), ft_wstr_to_str(wc), pf->spec);
        }
        else
        {
            join_value(&(pf->output), ft_strdup("(null)"), pf->spec);
        }
    }
	else if (pf->spec.type == C || (pf->spec.type == c && pf->spec.flag2 == l))
	{
		wchar_t wc = va_arg(pf->argptr, wchar_t);
        if (!wc)
        {
            join_value(&(pf->output), init_min_str(42), pf->spec);
            (pf->output)[(int)ft_strlen(pf->output) - 1] = '\000';
            ft_output(pf->fd, pf->output, &(pf->length));
            pf->output = ft_strdup("");
            (pf->length)++;
            write(pf->fd, "\000", 1);
        }
        else
        {
            wchar_t *wstr = (wchar_t *) malloc(sizeof(wchar_t) * 2);
            wstr[0] = wc;
            wstr[1] = 0;
            join_value(&(pf->output), ft_wstr_to_str(wstr), pf->spec);
        }
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
    {
        int my_char = va_arg(pf->argptr, int);
        if (my_char)
            join_value(&(pf->output), init_min_str(my_char), pf->spec);
        else
        {
            join_value(&(pf->output), init_min_str('*'), pf->spec);
			if (pf->spec.width >= 2 && pf->spec.minus_flag)
			{
				char *until;
				int null_pos = (int)ft_strlen(pf->output) - pf->spec.width;
				until = ft_strnew(null_pos);
				ft_memmove(until, pf->output, null_pos);
				ft_output(pf->fd, until, &(pf->length));
				write(pf->fd, "\000", 1);
				(pf->length)++;
				pf->output += null_pos + 1;
			}
			else
			{
				(pf->output)[(int)ft_strlen(pf->output) - 1] = '\000';
				ft_output(pf->fd, pf->output, &(pf->length));
				pf->output = ft_strdup("");
				(pf->length)++;
				write(pf->fd, "\000", 1);
			}
        }

    }
	else if (pf->spec.type == s)
	{
		char *res = va_arg(pf->argptr, char *);
		if (!res)
			res = ft_strdup("(null)");
		else
			res = ft_strdup(res);
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
    char        *first_spec;

    first_spec = NULL;
    pf.length = 0;
    pf.fd = 1;
    if (!(first_spec = ft_strchr(format, '%')))
		return (ft_output(pf.fd, format, &(pf.length)));
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
	ft_output(pf.fd, pf.output, &(pf.length));
    ft_strdel(&(pf.output));
    ft_lstdel(&(pf.t), &del_one);
	return (pf.length);
}
