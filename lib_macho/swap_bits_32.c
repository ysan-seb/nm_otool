/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits_32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:16:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 13:22:52 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

uint32_t		swap_bits_32(uint32_t n)
{
	return (((n & 0xff000000) >> 24) | ((n & 0x00ff0000) >> 8)
			| ((n & 0x0000ff00) << 8) | ((n & 0x000000ff) << 24));
}