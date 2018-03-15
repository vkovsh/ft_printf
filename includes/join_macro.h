/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_macro.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:39:56 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/15 16:50:40 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_MACRO_H
# define JOIN_MACRO_H
# include "data_structs.h"

void	join_none(t_pfargs *pf);
void	join_n(t_pfargs *pf);
void	join_t(t_pfargs *pf);
void	join_r(t_pfargs *pf);
void	join_big_s(t_pfargs *pf);
void	join_big_c(t_pfargs *pf);
void	join_signed_decimal(t_pfargs *pf);
void	join_unsigned_value(t_pfargs *pf);
void	join_c(t_pfargs *pf);
void	join_s(t_pfargs *pf);
void	join_percent(t_pfargs *pf);
void	join_p(t_pfargs *pf);	
#endif
