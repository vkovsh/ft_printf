/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:16:23 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 19:22:24 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		join_p(t_pfargs *pf)
{
	char	*to_del;
	t_value	*element;

	element = (t_value *)((pf->t)->content);
	element->value = ft_strtolower(ft_ulltoa_base(va_arg(pf->argptr, unsigned long long), 16));
	to_del = element->value;
	element->value = ft_strjoin("0x", to_del);
	ft_strdel(&to_del);
	join_value(&(pf->output), element->value, pf->spec);
}
