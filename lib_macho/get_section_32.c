/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:36:29 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 18:25:46 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct section	*get_section_32(t_stat stat, void *ptr, uint32_t magic, size_t offset)
{
	struct section	*section;

	if (checkoff(stat, ptr, offset + sizeof(struct section)) == ERR)
		return (NULL);
	section = (struct section *)(ptr + offset);
	if (magic == MH_MAGIC)
		return (section);
	// section->addr = swap_bits_32(section->addr);
	// section->size = swap_bits_32(section->size);
	section->offset = swap_bits_32(section->offset);
	// section->align = swap_bits_32(section->align);
	// section->reloff = swap_bits_32(section->reloff);
	// section->nreloc = swap_bits_32(section->nreloc);
	// section->flags = swap_bits_32(section->flags);
	// section->reserved1 = swap_bits_32(section->reserved1);
	// section->reserved2 = swap_bits_32(section->reserved2);
	return (section);
}
