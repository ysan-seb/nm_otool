/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:39:33 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/01 12:58:51 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_32(t_stat stat, void *ptr)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct mach_header		*header;
	struct load_command		*lc;

	i = 0;
	header = get_mach_header_32(stat, ptr, 0);
	if (!header)
		return (ERR);
	ncmds = swap_or_32(header->magic, header->ncmds);
	lc = get_load_command(stat, ptr, sizeof(struct mach_header));
	if (!lc)
		return (ERR);
	while (i < ncmds)
	{
		if (parse_segment_32(stat, header, lc) == ERR)
			return (ERR);
		lc = get_load_command(stat, (void*)lc,
		swap_or_32(header->magic, lc->cmdsize));
		if (!lc)
			return (ERR);
		i++;		
	}
	return (OK);
}
