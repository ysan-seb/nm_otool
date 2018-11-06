/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:37:01 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 18:00:12 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct section_64	*get_section_64(t_stat stat,
		void *ptr, uint32_t magic, size_t offset)
{
	struct section_64	*section;

	if (checkoff(stat, ptr, offset + sizeof(struct section_64)) == ERR)
		return (NULL);
	section = (struct section_64 *)(ptr + offset);
	if (magic == MH_MAGIC_64)
		return (section);
	section->offset = swap_bits_32(section->offset);
	return (section);
}
