/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:51:24 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/13 14:49:53 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int     ft_output(const int fd, const char *output, int *const length)
{
    int len;

    len = ft_strlen(output);
	/*while (*output)
	{
		printf("|%d| ", *output);
		output++;
	}
	printf("\n");
	exit(0);*/
    if (!(*length))
	    *length = len;
    else
        *length += len;
	write(fd, output, len);
	return (*length);
}
