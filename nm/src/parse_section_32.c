/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_section_32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:27:29 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 20:36:17 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		check_section_32(t_stat *stat, struct section *sect, int i)
{
	if (strcmp(sect->sectname, SECT_TEXT) == OK)
		stat->tss = i + 1;
	else if (strcmp(sect->sectname, SECT_DATA) == OK)
		stat->dss = i + 1;
	else if (strcmp(sect->sectname, SECT_BSS) == OK)
		stat->bss = i + 1;
}

int				parse_section_32(t_stat *stat,
		struct mach_header *header, struct load_command *lc)
{
	int						i;
	struct section			*sect;
	struct segment_command	*seg;

	seg = get_segment_command_32(*stat, (void*)lc, header->magic, 0);
	if (seg == NULL)
		return (ERR);
	i = 0;
	if (strcmp(seg->segname, "__TEXT") == 0 ||
	strcmp(seg->segname, "__DATA") == 0 || header->filetype == MH_OBJECT)
	{
		sect = get_section_32(*stat, (void*)(seg + 1), header->magic, 0);
		while (i < (int)seg->nsects)
		{
			check_section_32(stat, sect, stat->i_sect);
			i++;
			stat->i_sect++;
			sect = get_section_32(*stat, (void*)sect, header->magic, sizeof(struct section));
			if (!sect)
				return (ERR);
		}
	}
	return (OK);
}
