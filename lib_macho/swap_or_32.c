/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_or_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:39:30 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 18:01:53 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

uint32_t			swap_or_32(uint32_t magic, uint32_t value)
{
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 ||
			magic == FAT_MAGIC || magic == FAT_MAGIC_64)
		return (value);
	return (swap_bits_32(value));
}
