/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:48:52 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 17:57:31 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		parse_segment_64(
		t_stat stat, struct mach_header_64 *h, struct load_command *lc)
{
	struct segment_command_64	*seg;

	if (lc->cmd == LC_SEGMENT_64)
	{
		seg = get_segment_command_64(stat, (void*)lc, h->magic, 0);
		if (seg == NULL)
			return (ERR);
		if (strcmp(seg->segname, "__TEXT") == 0 ||
			h->filetype == MH_OBJECT)
			output_64(stat, h, seg);
	}
	return (OK);
}
