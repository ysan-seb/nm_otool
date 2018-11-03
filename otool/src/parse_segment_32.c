/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:47:34 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/30 15:56:27 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		parse_segment_32(
		t_stat stat, struct mach_header *header, struct load_command *lc)
{
	struct segment_command	*seg;

	if (swap_or_32(header->magic, lc->cmd) == LC_SEGMENT)
	{
		seg = get_segment_command_32(stat, (void*)lc, 0);
		if (seg == NULL)
			return (ERR);
		if (strcmp(seg->segname, "__TEXT") == 0 ||
				swap_or_32(header->magic, header->filetype) == MH_OBJECT)
			output_32(stat, header, seg);
	}
	return (OK);
}
