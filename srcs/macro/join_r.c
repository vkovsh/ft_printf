/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:02:44 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 17:08:56 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				join_r(t_pfargs *pf)
{
	unsigned char	*np;
	char			*octal;
	
	np = va_arg(pf->argptr, unsigned char *);
	octal = ft_strnew(0);
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
