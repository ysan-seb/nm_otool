/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fat_arch_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:30:34 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 17:59:37 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct fat_arch		*get_fat_arch_32(t_stat stat,
		void *ptr, uint32_t magic, size_t offset)
{
	struct fat_arch	*arch;

	if (checkoff(stat, ptr, offset + sizeof(struct fat_arch)) == ERR)
		return (NULL);
	arch = (struct fat_arch *)(ptr + offset);
	if (magic == FAT_MAGIC)
		return (arch);
	arch->cputype = swap_bits_32(arch->cputype);
	arch->cpusubtype = swap_bits_32(arch->cpusubtype);
	arch->offset = swap_bits_32(arch->offset);
	return (arch);
}
