/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_or_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:47:20 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 18:01:44 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

uint16_t			swap_or_16(uint32_t magic, uint16_t value)
{
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 ||
			magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		return (value);
	return (swap_bits_16(value));
}
