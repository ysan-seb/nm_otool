/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:37:01 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 18:26:02 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct section_64	*get_section_64(t_stat stat, void *ptr, uint32_t magic, size_t offset)
{
	struct section_64	*section;

	if (checkoff(stat, ptr, offset + sizeof(struct section_64)) == ERR)
		return (NULL);
	section = (struct section_64 *)(ptr + offset);
	if (magic == MH_MAGIC_64)
		return (section);
	// section->addr = swap_bits_64(section->addr);
	// section->size = swap_bits_64(section->size);
	section->offset = swap_bits_32(section->offset);
	// section->align = swap_bits_32(section->align);
	// section->reloff = swap_bits_32(section->reloff);
	// section->nreloc = swap_bits_32(section->nreloc);
	// section->flags = swap_bits_32(section->flags);
	// section->reserved1 = swap_bits_32(section->reserved1);
	// section->reserved2 = swap_bits_32(section->reserved2);
	// section->reserved3 = swap_bits_32(section->reserved3);
	return (section);
}
