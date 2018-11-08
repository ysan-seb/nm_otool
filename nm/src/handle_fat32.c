/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:02:06 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/08 14:51:28 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			arch_type(t_stat *stat, struct fat_arch *arch)
{
	if (arch->cputype == CPU_TYPE_POWERPC)
		strcpy((*stat).arch_name, "(for architecture ppc)");
	else if (arch->cputype == CPU_TYPE_I386)
		strcpy((*stat).arch_name, "(for architecture i386)");
	else
		(*stat).arch_name[0] = '\0';
	return (OK);
}

static int			x86_64_not_found(t_stat s, void *ptr)
{
	size_t				nfat_arch;
	struct fat_header	*header;
	struct fat_arch		*arch;

	header = (struct fat_header *)ptr;
	if (!header)
		return (ERR);
	nfat_arch = header->nfat_arch;
	arch = (struct fat_arch *)(ptr + sizeof(struct fat_header));
	if (!arch)
		return (ERR);
	while (nfat_arch--)
	{
		if (checkoff(s, ptr, arch->offset))
			return (ERR);
		arch_type(&s, arch);
		if (nm(s, ptr + arch->offset) == ERR)
			return (ERR);
		arch = (void*)arch + sizeof(struct fat_arch);
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
	nfat_arch = header->nfat_arch;
	arch = get_fat_arch_32(s, ptr, header->magic, sizeof(struct fat_header));
	if (!arch)
		return (ERR);
	while (nfat_arch--)
	{
		if (checkoff(s, ptr, arch->offset))
			return (ERR);
		if (header->nfat_arch == 1)
			printf("%s:\n", s.filename);
		if (arch->cputype == CPU_TYPE_X86_64 || header->nfat_arch == 1)
			return (nm(s, s.ptr + arch->offset));
		arch = get_fat_arch_32(s, arch, header->magic, sizeof(struct fat_arch));
		if (!arch)
			return (ERR);
	}
	x86_64_not_found(s, ptr);
	return (OK);
}
