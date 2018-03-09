/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:51:24 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/09 12:19:07 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_output(const int fd, const char *output, int *const length)
{
	*length = ft_strlen(output);
	write(fd, output, *length);
	return (*length);
}
