/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 14:55:22 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 14:56:20 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		if (**txt_pointer == '*')
		{
			(*(txt_pointer))++;
			spec->width = 0;
			spec->asterisk_width = TRUE;
		}
	}
	else if (**txt_pointer == '*')
	{
		(*(txt_pointer))++;
		spec->width = 0;
		spec->asterisk_width = TRUE;
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
	}
	else
		spec->width = 0;
}
