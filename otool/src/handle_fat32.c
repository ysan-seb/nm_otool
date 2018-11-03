/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:04:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 12:20:46 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int			arch_type(t_stat *stat,
		struct fat_header *header, struct fat_arch *arch)
{
	if (swap_or_32(header->magic, arch->cputype) == CPU_TYPE_POWERPC)
		strcpy((*stat).arch_name, "(architecture ppc)");
	else if (swap_or_32(header->magic, arch->cputype) == CPU_TYPE_I386)
		strcpy((*stat).arch_name, "(architecture i386)");
	else
		(*stat).arch_name[0] = '\0';
	return (OK);
}

static int			x86_64_not_found(t_stat stat, void *ptr)
{
	size_t				nfat_arch;
	struct fat_header	*header;
	struct fat_arch		*arch;

	header = get_fat_header(stat, ptr, 0);
	if (!header)
		return (ERR);
	nfat_arch = swap_or_32(header->magic, header->nfat_arch);
	arch = get_fat_arch_32(stat, ptr, sizeof(struct fat_header));
	if (!arch)
		return (ERR);
	while (nfat_arch--)
	{
		if (checkoff(stat, ptr, swap_or_32(header->magic, arch->offset)))
			return (ERR);
		arch_type(&stat, header, arch);
		otool(stat, stat.ptr + swap_or_32(header->magic, arch->offset));
		arch = get_fat_arch_32(stat, arch, sizeof(struct fat_arch));
		if (!arch)
			return (ERR);
	}
	return (OK);
}

int					handle_fat_32(t_stat s, void *ptr)
{
	size_t				nfat_arch;
	struct fat_header	*header;
	struct fat_arch		*arch;

	header = get_fat_header(s, ptr, 0);
	if (!header)
		return (ERR);
	nfat_arch = swap_or_32(header->magic, header->nfat_arch);
	arch = get_fat_arch_32(s, ptr, sizeof(struct fat_header));
	if (!arch)
		return (ERR);
	while (nfat_arch--)
	{
		if (checkoff(s, ptr, swap_or_32(header->magic, arch->offset)))
			return (ERR);
		if (swap_or_32(header->magic, arch->cputype) == CPU_TYPE_X86_64)
			return (otool(s, s.ptr + swap_or_32(header->magic, arch->offset)));
		arch = get_fat_arch_32(s, arch, sizeof(struct fat_arch));
		if (!arch)
			return (ERR);
	}
	return (x86_64_not_found(s, ptr));
}
