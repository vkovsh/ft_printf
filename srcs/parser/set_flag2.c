/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:12:05 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 16:02:34 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_hh(char **str, t_spec *spec)
{
	(*str)++;
	if (**str == 'h')
	{
		spec->flag2 = hh;
		(*str)++;
	}
	else
		spec->flag2 = h;
}

static void		ft_ll(char **str, t_spec *spec)
{
	(*str)++;
	if (**str == 'l')
	{
		spec->flag2 = ll;
		(*str)++;
	}
	else
		spec->flag2 = l;
}

static void		ft_realloc(char *new, char **old)
{
	//char		*to_del;
	
	//to_del = *old;
	*old = ft_strdup(new);
	//ft_strdel(&to_del);
}

void			set_flag2(char **txt_pointer, t_spec *spec)
{
	char		*str;

	str = *txt_pointer;
	if (str[0] == 'h')
		ft_hh(&str, spec);
	else if (str[0] == 'l')
		ft_ll(&str, spec);
	else if (str[0] == 'j')
	{
		str++;
		spec->flag2 = j;
	}
	else if (str[0] == 'z')
	{
		str++;
		spec->flag2 = z;
	}
	else
		spec->flag2 = IGNORE2;
	if (*txt_pointer != str)
		ft_realloc(str, txt_pointer);
}
