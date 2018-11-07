/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:47:34 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 17:56:44 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		parse_segment_32(
		t_stat stat, struct mach_header *h, struct load_command *lc)
{
	struct segment_command	*seg;

	if (lc->cmd == LC_SEGMENT)
	{
		seg = get_segment_command_32(stat, (void*)lc, h->magic, 0);
		if (seg == NULL)
			return (ERR);
		if (strcmp(seg->segname, "__TEXT") == 0 ||
			h->filetype == MH_OBJECT)
			output_32(stat, h, seg);
	}
	return (OK);
}
