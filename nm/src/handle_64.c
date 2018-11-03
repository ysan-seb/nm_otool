/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:26:48 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 18:29:51 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// void swap_arr(struct nlist_64 *a, struct nlist_64 *b)
// {
// 	struct nlist_64 c;

// 	c = *a;
// 	*a = *b;
// 	*b = c;
// }

// struct nlist_64 *sort_ascii(t_stat stat, void *ptr, struct mach_header_64 *header, struct symtab_command *s)
// {
// 	uint32_t i;
// 	struct nlist_64 *array;
// 	char *stringtable;
// 	char *s1;
// 	char *s2;

// 	i = 0;
// 	if (checkoff(stat, ptr, swap_or_32(header->magic, s->symoff)) == ERR || checkoff(stat, ptr, swap_or_32(header->magic, s->stroff)) == ERR)
// 		return (NULL);
// 	array = (void *)ptr + swap_or_32(header->magic, s->symoff);
// 	stringtable = (void *)ptr + swap_or_32(header->magic, s->stroff);
// 	while (i + 1 < swap_or_32(header->magic, s->nsyms))
// 	{
// 		s1 = stringtable + swap_or_32(header->magic, array[i].n_un.n_strx);
// 		s2 = stringtable + swap_or_32(header->magic, array[i + 1].n_un.n_strx);
// 		if (strcmp(s1, s2) > 0)
// 		{
// 			swap_arr(&array[i], &array[i + 1]);
// 			i = -1;
// 		}
// 		i++;
// 	}
// 	return (array);
// }

int build_list64(t_stat stat,
				 struct mach_header_64 *h, struct symtab_command *s, void *p)
{
	// struct nlist_64 *a;

	// if (checkoff(stat, p, swap_or_32(h->magic, s->symoff)) == ERR)
	// 	return (ERR);
	// a = sort_ascii(stat, p, h, s);

	return (output64(stat, h, s, p));
}

int handle_64(t_stat stat, void *ptr)
{
	uint32_t i;
	uint32_t ncmds;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;

	i = 0;
	header = get_mach_header_64(stat, ptr, 0);
	if (!header)
		return (ERR);
	stat.i_sect = 0;	
	ncmds = swap_or_32(header->magic, header->ncmds);
	lc = get_load_command(stat, ptr, sizeof(struct mach_header_64));
	if (!lc)
		return (ERR);
	while (i < ncmds)
	{
		if (swap_or_32(header->magic, lc->cmd) == LC_SEGMENT_64)
			if (parse_section_64(&stat, header, lc) == ERR)
				return (ERR);
		if (swap_or_32(header->magic, lc->cmd) == LC_SYMTAB)
		{
			sym = get_symtab_command(stat, lc, 0);
			if (!sym)
				return (ERR);
			if (build_list64(stat, header, sym, ptr) == ERR)
				return (ERR);
			break;
		}
		lc = get_load_command(stat, (void *)lc,
							  swap_or_32(header->magic, lc->cmdsize));
		if (!lc)
			return (ERR);
		i++;
	}
	stat.i_sect = 0;
	return (OK);
}
