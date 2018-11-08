/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_modulo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 15:35:38 by ysan-seb          #+#    #+#             */
/*   Updated: 2017/07/12 15:35:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_modulo(t_env *e)
{
	char *s;

	s = ft_strnew(2);
	s[0] = '%';
	s[1] = '\0';
	e->precision = 0;
	ft_printf_putflags(e, s);
}