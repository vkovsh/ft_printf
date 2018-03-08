/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:59:20 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/06 17:47:01 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "my_bool.h"
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef enum 		e_flag1
{
	IGNORE1 = 0,
	SHARP = '#',
	ZERO = '0',
	MINUS = '-',
	PLUS = '+',
	SPACE = '\040'
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
	none = 0,
    r = 'r',
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
	B = 'B',
	PERCENT = '\033'
}					t_type;

typedef struct  	s_color
{
	unsigned char 	r;
	unsigned char 	g;
	unsigned char 	b;	
}					t_color;

typedef struct  	s_spec
{
	struct s_color 	color;
	struct s_color 	background;
	enum e_bool		sharp_flag;
	enum e_bool		zero_flag;
	enum e_bool		minus_flag;
	enum e_bool		plus_flag;
	enum e_bool		space_flag;
	enum e_bool 	asterisk_width;
	enum e_bool 	asterisk_precision;
	enum e_bool 	asterisk_color;
	enum e_bool 	asterisk_background;
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

int                 ft_dprintf(int fd, const char *format, ...);

t_spec				get_spec(char **txt_pointer);

void				join_value(char **output, char *value, t_spec spec);

char				*ft_wstr_to_str(wchar_t *ws);

void				set_signed_decimal(t_pfargs *pf);

void				set_unsigned_value(t_pfargs *pf);

void                del_one(void *content, size_t content_size);

void			    set_value(t_pfargs *pf);

void			    set_spec(t_pfargs *pf);

void			    check_asterisk(t_pfargs *pf);

void			    init_list(const char *format, t_list **t, char **output);

int				    ft_output(const int fd, const char *output, int *const length);

void		        check_double_percent(char *format);

t_value             *fresh_value(t_type t, void *data, size_t count);

char			    *init_min_str(int c);

void			    init_list(const char *format, t_list **t, char **output);

void				parse_specs(char *format, t_list **parsed_values);
#endif
