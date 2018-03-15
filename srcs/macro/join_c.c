/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:48:32 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 19:08:33 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		join_c(t_pfargs *pf)
{
	int		my_char;
	t_value	*element;
	
	my_char = va_arg(pf->argptr, int);
	element = ((t_value *)((pf->t)->content));
	if (my_char)
	{
		element->value = init_min_str(my_char);
		join_value(&(pf->output), element->value, pf->spec);
	}
	else
	{
		element->value = init_min_str('*');
		join_value(&(pf->output), element->value, pf->spec);
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
