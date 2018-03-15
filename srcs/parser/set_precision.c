/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:05:59 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 15:07:11 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		else
		{
			spec->precision = 0;
		}
		*txt_pointer = str;
	}
	else
		spec->precision = -1;
}
