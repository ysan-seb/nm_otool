/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fat_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:33:00 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 13:35:31 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct fat_header	*get_fat_header(t_stat stat, void *ptr, size_t offset)
{
	struct fat_header	*header;

	if (checkoff(stat, ptr, offset + sizeof(struct fat_header)) == ERR)
		return (NULL);
	header = (struct fat_header *)(ptr + offset);
	if (header->magic == FAT_MAGIC)
		return (header);
	header->nfat_arch = swap_bits_32(header->nfat_arch);
	return (header);
}
