/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:26:48 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/06 16:25:04 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		parse_command_64(t_stat stat,
		struct mach_header_64 *header, struct load_command *lc, void *ptr)
{
	uint32_t				i[2];
	struct symtab_command	*sym;

	i[0] = 0;
	i[1] = header->ncmds;
	while (i[0]++ < i[1] - 1)
	{
		if (lc->cmd == LC_SEGMENT_64
			&& parse_section_64(&stat, header, lc) == ERR)
			return (ERR);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = get_symtab_command(stat, (void*)lc, header->magic, 0);
			if (!sym)
				return (ERR);
			if (output64(stat, header, sym, ptr) == ERR)
				return (ERR);
			break ;
		}
		lc = get_load_command(stat, (void*)lc, header->magic, lc->cmdsize);
		if (!lc)
			return (ERR);
	}
	return (OK);
}

int		handle_64(t_stat stat, void *ptr)
{
	struct mach_header_64	*header;
	struct load_command		*lc;

	stat.i_sect = 0;
	header = get_mach_header_64(stat, ptr, 0);
	if (!header)
		return (ERR);
	lc = get_load_command(stat,
		ptr, header->magic, sizeof(struct mach_header_64));
	if (!lc)
		return (ERR);
	return (parse_command_64(stat, header, lc, ptr));
}
