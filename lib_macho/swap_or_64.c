/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_or_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:44:24 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/30 15:43:18 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

static uint64_t		swap_bits_64(uint64_t n)
{
	return (((n & 0xff00000000000000ULL) >> 56) |
			((n & 0x00ff000000000000ULL) >> 40) |
			((n & 0x0000ff0000000000ULL) >> 24) |
			((n & 0x000000ff00000000ULL) >> 8) |
			((n & 0x00000000ff000000ULL) << 8) |
			((n & 0x0000000000ff0000ULL) << 24) |
			((n & 0x000000000000ff00ULL) << 40) |
			((n & 0x00000000000000ffULL) << 56));
}

uint64_t			swap_or_64(uint32_t magic, uint64_t value)
{
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 ||
			magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		return (value);
	return (swap_bits_64(value));
}
