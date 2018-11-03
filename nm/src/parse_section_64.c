/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_section_64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:28:30 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 18:30:19 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		check_section_64(t_stat *stat, struct section_64 *sect, int i)
{
	if (strcmp(sect->sectname, SECT_TEXT) == OK)
		stat->tss = i + 1;
	else if (strcmp(sect->sectname, SECT_DATA) == OK)
		stat->dss = i + 1;
	else if (strcmp(sect->sectname, SECT_BSS) == OK)
		stat->bss = i + 1;
}

int				parse_section_64(t_stat *stat,
		struct mach_header_64 *header, struct load_command *lc)
{
	int							i;
	struct section_64			*sect;
	struct segment_command_64	*seg;

	seg = get_segment_command_64(*stat, (void*)lc, 0);
	if (seg == NULL)
		return (ERR);
	i = 0;
	if (strcmp(seg->segname, "__TEXT") == 0 || strcmp(seg->segname, "__DATA") == 0 ||
			swap_or_32(header->magic, header->filetype) == MH_OBJECT)
	{
		sect = get_section_64(*stat, (void*)(seg + 1), 0);
		while (i < (int)swap_or_32(header->magic, seg->nsects))
		{
			check_section_64(stat, sect, stat->i_sect);
			i++;
			stat->i_sect++;
			sect = get_section_64(*stat,
					(void*)(sect), sizeof(struct section_64));
			if (!sect)
				return (ERR);
		}
	}
	return (OK);
}
