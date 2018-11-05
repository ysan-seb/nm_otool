/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:34:53 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 21:03:34 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		parse_command_32(t_stat stat,
		struct mach_header *header, struct load_command *lc, void *ptr)
{
	uint32_t				i[2];
	struct symtab_command	*sym;

	i[0] = 0;
	i[1] = header->ncmds;
	stat.i_sect = 0;
	while (i[0] < i[1])
	{
		if (lc->cmd == LC_SEGMENT) 
			if (parse_section_32(&stat, header, lc) == ERR)
				return (ERR);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = get_symtab_command(stat, (void*)lc, header->magic, 0);
			if (!sym)
				return (ERR);
			if (output32(stat, header, sym, ptr) == ERR)
				return (ERR);
			break ;
		}
		lc = get_load_command(stat, (void*)lc, header->magic, lc->cmdsize);
		if (!lc)
			return (ERR);
		i[0]++;
	}
	stat.i_sect = 0;
	return (OK);
}

int		handle_32(t_stat stat, void *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;

	header = get_mach_header_32(stat, ptr, 0);
	if (!header)
		return (ERR);
	lc = get_load_command(stat, ptr, header->magic, sizeof(struct mach_header));
	if (!lc)
		return (ERR);
	return (parse_command_32(stat, header, lc, ptr));
}