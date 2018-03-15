/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:22:21 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 15:23:10 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_color(char **txt_pointer, t_spec *spec)
{
	char 		*str;

	str = *txt_pointer;
	if (str[0] == '{' && ft_strlen(str) > 7 && str[7] == '}')
	{
		if (ft_ishex(str[1]) &&
			ft_ishex(str[2]) &&
			ft_ishex(str[3]) &&
			ft_ishex(str[4]) &&
			ft_ishex(str[5]) &&
			ft_ishex(str[6]))
		{
			spec->color.r = (str[1] <= '9') ? (str[1] - '0') * 16 : (str[1] - 87) * 16;
			spec->color.r += (str[2] <= '9') ? (str[2] - '0') : (str[2] - 87);
			spec->color.g = (str[3] <= '9') ? (str[3] - '0') * 16 : (str[3] - 87) * 16;
			spec->color.g += (str[4] <= '9') ? (str[4] - '0') : (str[4] - 87);
			spec->color.b = (str[5] <= '9') ? (str[5] - '0') * 16 : (str[5] - 87) * 16;
			spec->color.b += (str[6] <= '9') ? (str[6] - '0') : (str[6] - 87);
			(*txt_pointer) += 8;
		}
	}
	else if (str[0] == '{' && ft_strlen(str) > 2 && str[2] == '}' && str[1] == '*')
	{
		spec->asterisk_color = TRUE;
		spec->color.r = 0;
		spec->color.g = 0;
		spec->color.b = 0;
		*(txt_pointer) += 3;
	}
	else
	{
		spec->asterisk_color = FALSE;
		spec->color.r = 0;
		spec->color.g = 0;
		spec->color.b = 0;
	}
}
