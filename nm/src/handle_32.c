/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:34:53 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 19:03:50 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int build_list32(t_stat stat,
				 struct mach_header *h, struct symtab_command *s, void *p)
{
	// struct nlist_64 *a;

	// if (checkoff(stat, p, swap_or_32(h->magic, s->symoff)) == ERR)
	// 	return (ERR);
	// a = sort_ascii(stat, p, h, s);

	return (output32(stat, h, s, p));
}

int		parse_command_32(t_stat stat, struct mach_header *header, struct load_command *lc, void *ptr)
{
	uint32_t				i;
	uint32_t				ncmds;
	struct symtab_command	*sym;

	i = 0;
	stat.i_sect = 0;
	ncmds = swap_or_32(header->magic, header->ncmds);
	while (i < ncmds)
	{
		if (swap_or_32(header->magic, lc->cmd) == LC_SEGMENT)
			parse_section_32(&stat, header, lc);
		if (swap_or_32(header->magic, lc->cmd) == LC_SYMTAB)
		{
			sym = get_symtab_command(stat, lc, 0);
			if (!sym)
				return (ERR);
			if (build_list32(stat, header, sym, ptr) == ERR)
				return (ERR);
			break ;
		}
		lc = get_load_command(stat, (void*)lc,
		swap_or_32(header->magic, lc->cmdsize));
		if (!lc)
			return (ERR);
		i++;		
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
	lc = get_load_command(stat, ptr, sizeof(struct mach_header));
	if (!lc)
		return (ERR);
	return (parse_command_32(stat, header, lc, ptr));
}
