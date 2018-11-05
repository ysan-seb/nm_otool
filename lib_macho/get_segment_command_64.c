/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_segment_command_64.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:38:36 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 20:22:50 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct segment_command_64	*get_segment_command_64(t_stat stat, void *ptr, uint32_t magic, size_t offset)
{
	struct segment_command_64	*segment;

	if (checkoff(stat, ptr, offset + sizeof(struct segment_command_64)) == ERR)
		return (NULL);
	segment = (struct segment_command_64 *)(ptr + offset);
	if (magic == MH_MAGIC_64)
		return (segment);
	// segment->vmaddr = swap_bits_64(segment->vmaddr);
	// segment->vmsize = swap_bits_64(segment->vmsize);
	// segment->fileoff = swap_bits_64(segment->fileoff);
	// segment->filesize = swap_bits_64(segment->filesize);
	segment->nsects = swap_bits_32(segment->nsects);
	// segment->flags = swap_bits_32(segment->flags);
	return (segment);
}
