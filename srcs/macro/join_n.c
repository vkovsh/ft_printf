/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:54:46 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 16:56:17 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	join_n(t_pfargs *pf)
{
	int	*count;

	count = va_arg(pf->argptr, int *);
	*count = (int)ft_strlen(pf->output);
}
