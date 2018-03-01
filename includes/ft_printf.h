/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:59:20 by vkovsh            #+#    #+#             */
/*   Updated: 2018/02/21 18:24:54 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "my_bool.h"
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdarg.h>

typedef enum 		e_flag1
{
	IGNORE1 = 0,
	SHARP = '#',
	ZERO = '0',
	MINUS = '-',
	PLUS = '+',
	SPACE = '\32'
}					t_flag1;

typedef enum 		e_flag2
{
	IGNORE2 = 0,
	hh = 'H',
	h = 'h',
	ll = 'L',
	l = 'l',
	j = 'j',
	z = 'z'
}					t_flag2;

typedef enum 		e_type
{
	s = 's',
	S = 'S',
	p = 'p',
	d = 'd',
	D = 'D',
	i = 'i',
	o = 'o',
	O = 'O',
	u = 'u',
	U = 'U',
	x = 'x',
	X = 'X',
	c = 'c',
	C = 'C',
	T = 'T',
	b = 'b',
	PERCENT = '\033'
}					t_type;

typedef struct  	s_spec
{
	enum e_bool		sharp_flag;
	enum e_bool		zero_flag;
	enum e_bool		minus_flag;
	enum e_bool		plus_flag;
	enum e_bool		space_flag;
	enum e_bool 	asterisk_width;
	enum e_bool 	asterisk_precision;
	int				width;
	int				precision;
	enum e_flag2	flag2;	
	enum e_type		type;
}					t_spec;

typedef struct  	s_value
{
	struct s_spec	spec;
	void			*value;
}					t_value;

typedef struct		s_pfargs
{
	va_list			argptr;
	struct s_list	*t;
	char			*output;
	int				length;
	struct s_spec	spec;
}					t_pfargs;

int					ft_printf(const char *format, ...);

t_spec				get_spec(char **txt_pointer);

void				join_value(char **output, char *value, t_spec spec);
#endif
