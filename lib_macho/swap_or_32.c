/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_or_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:39:30 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 16:00:48 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

static uint32_t		swap_bits_32(uint32_t n)
{
	return (((n & 0xff000000) >> 24) | ((n & 0x00ff0000) >> 8)
			| ((n & 0x0000ff00) << 8) | ((n & 0x000000ff) << 24));
}

uint32_t			swap_or_32(uint32_t magic, uint32_t value)
{
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 ||
			magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		return (value);
	return (swap_bits_32(value));
}
