/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:48:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/30 15:56:28 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		parse_segment_64(
		t_stat stat, struct mach_header_64 *header, struct load_command *lc)
{
	struct segment_command_64	*seg;

	if (lc->cmd == LC_SEGMENT_64)
	{
		seg = get_segment_command_64(stat, (void*)lc, 0);
		if (seg == NULL)
			return (ERR);
		if (strcmp(seg->segname, "__TEXT") == 0 ||
				swap_or_32(header->magic, header->filetype) == MH_OBJECT)
			output_64(stat, header, seg);
	}
	return (OK);
}
