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

void			check_asterisk(t_pfargs *pf)
{
	int 		color_nbr;
	t_color		color;

	if (pf->spec.width && pf->spec.asterisk_width)
		va_arg(pf->argptr, void *);
	else if (pf->spec.asterisk_width)
		pf->spec.width = va_arg(pf->argptr, int);
	if (pf->spec.width < 0)
	{
		pf->spec.width *= -1;
		pf->spec.minus_flag = TRUE;
	}
	if (pf->spec.asterisk_precision)
		pf->spec.precision = va_arg(pf->argptr, int);
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
    	join_none(pf);
    else if (pf->spec.type == n)
    	join_n(pf);
	else if (pf->spec.type == T)
		join_t(pf);
	else if (pf->spec.type == r)
		join_r(pf);
	else if (pf->spec.type == S || (pf->spec.type == s && pf->spec.flag2 == l))
	{
		pf->spec.type = S;
    	join_big_s(pf);
	}
	else if (pf->spec.type == C || (pf->spec.type == c && pf->spec.flag2 == l))
	{
		pf->spec.type = C;
		join_big_c(pf);
	}
	else if (pf->spec.type == d || pf->spec.type == i || pf->spec.type == D)
		join_signed_decimal(pf);
	else if (is_unsigned(pf->spec.type))
		join_unsigned_value(pf);
	else if (pf->spec.type == c)
    	join_c(pf);
	else if (pf->spec.type == s)
		join_s(pf);
	else if (pf->spec.type == PERCENT)
		join_percent(pf);
	else if (pf->spec.type == p)
		join_p(pf);
}

int				ft_printf(const char *format, ...)
{
	t_pfargs	pf;
    char        *first_spec;
    t_list		*tmp;

    first_spec = NULL;
    pf.length = 0;
    pf.fd = 1;
    if (!(first_spec = ft_strchr(format, '%')))
		return (ft_output(pf.fd, format, &(pf.length)));
	init_list(format, &(pf.t), &(pf.output));
	va_start(pf.argptr, format);
	tmp = pf.t;
	while (pf.t)
	{
		set_spec(&pf);
		check_asterisk(&pf);
		set_value(&pf);
		pf.t = (pf.t)->next;
	}
	va_end(pf.argptr);
	ft_output(pf.fd, pf.output, &(pf.length));
    ft_strdel(&(pf.output));
    ft_lstdel(&tmp, &del_one);
	return (pf.length);
}
