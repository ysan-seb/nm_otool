/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:46:32 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 17:54:44 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		handle_64(t_stat stat, void *ptr)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct mach_header_64	*h;
	struct load_command		*lc;

	i = 0;
	h = get_mach_header_64(stat, ptr, 0);
	if (!h)
		return (ERR);
	ncmds = h->ncmds;
	lc = get_load_command(stat, ptr, h->magic, sizeof(struct mach_header_64));
	if (!lc)
		return (ERR);
	while (i < ncmds)
	{
		if (parse_segment_64(stat, h, lc) == ERR)
			return (ERR);
		lc = get_load_command(stat, (void*)lc, h->magic, lc->cmdsize);
		if (!lc)
			return (ERR);
		i++;		
	}
	return (OK);
}
