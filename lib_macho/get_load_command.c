/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_load_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:34:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 17:59:13 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct load_command		*get_load_command(t_stat stat,
		void *ptr, uint32_t magic, size_t offset)
{
	struct load_command	*lc;

	if (checkoff(stat, ptr, offset + sizeof(struct load_command)) == ERR)
		return (NULL);
	lc = (struct load_command *)(ptr + offset);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64)
		return (lc);
	lc->cmd = swap_bits_32(lc->cmd);
	lc->cmdsize = swap_bits_32(lc->cmdsize);
	return (lc);
}
