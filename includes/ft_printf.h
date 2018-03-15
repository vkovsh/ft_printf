/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:59:20 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 17:41:58 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>
# include "join_macro.h"
# include "data_structs.h"

int					ft_printf(const char *format, ...);

int                 ft_dprintf(int fd, const char *format, ...);

t_spec				get_spec(char **txt_pointer);

void				join_value(char **output, char *value, t_spec spec);

void                del_one(void *content, size_t content_size);

void			    set_value(t_pfargs *pf);

void			    set_spec(t_pfargs *pf);

void			    check_asterisk(t_pfargs *pf);

void			    init_list(const char *format, t_list **t, char **output);

int				    ft_output(const int fd, const char *output, int *const length);

void		        check_double_percent(char *format);

t_value             fresh_value(t_type t, void *data, size_t count);

char			    *init_min_str(int c);

void			    init_list(const char *format, t_list **t, char **output);

void				parse_specs(char *format, t_list **parsed_values);

t_bool				is_unsigned(t_type t);

t_bool				is_flag1(char c);

t_bool				is_type(char c);

void 				set_flag1(char **txt_pointer, t_spec *spec);

void				set_width(char **txt_pointer, t_spec *spec);

void				set_precision(char **txt_pointer, t_spec *spec);

void				set_flag2(char **txt_pointer, t_spec *spec);

void				set_type(char **txt_pointer, t_spec *spec);

void				set_background(char **txt_pointer, t_spec *spec);

void				set_color(char **txt_pointer, t_spec *spec);
#endif
