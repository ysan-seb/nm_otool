/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:04:45 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 18:43:54 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int			arch_type(t_stat *stat, struct fat_arch *arch)
{
	if (arch->cputype == CPU_TYPE_POWERPC)
		strcpy((*stat).arch_name, "(architecture ppc)");
	else if (arch->cputype == CPU_TYPE_I386)
		strcpy((*stat).arch_name, "(architecture i386)");
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
		if (otool(s, ptr + arch->offset) == ERR)
			return (ERR);
		arch = (void*)arch + sizeof(struct fat_arch);
		if (!arch)
			return (ERR);
	}
	return (OK);
}

int					power_2(uint32_t align)
{
	int ret;

	ret = 1;
	while (align--)
		ret *= 2;
	return (ret);
}

int					disp_fat_header(t_stat s, void *ptr, struct fat_header *h)
{
	uint32_t		i;
	uint32_t		magic;
	struct fat_arch	*a;

	i = 0;
	magic = (h->magic == FAT_CIGAM) ? swap_bits_32(h->magic) : h->magic;
	if (checkoff(s, ptr, h->nfat_arch * sizeof(struct fat_arch) - 1))
		return (ERR);
	a = ptr + sizeof(struct fat_header);
	printf("Fat headers\nfat_magic 0x%x\nnfat_arch %u\n", magic, h->nfat_arch);
	while (i < h->nfat_arch)
	{
		printf("architecture %u\n", i);
		printf("    cputype %u\n", swap_or_32(h->magic, a->cputype));
		printf("    cpusubtype %u\n", (swap_or_32(h->magic, a->cpusubtype)
		== 2147483651) ? 3 : swap_or_32(h->magic, a->cpusubtype));
		printf("    offset %u\n", swap_or_32(h->magic, a->offset));
		printf("    size %u\n", swap_or_32(h->magic, a->size));
		printf("    align 2^%u (%d)\n", swap_or_32(h->magic, a->align),
		power_2(swap_or_32(h->magic, a->align)));
		a = (void*)a + sizeof(struct fat_arch);
		i++;
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
	(strchr(s.opt, 'f')) ? disp_fat_header(s, ptr, header) : 0;
	nfat_arch = header->nfat_arch;
	arch = get_fat_arch_32(s, ptr, header->magic, sizeof(struct fat_header));
	if (!arch)
		return (ERR);
	while (nfat_arch--)
	{
		if (checkoff(s, ptr, arch->offset))
			return (ERR);
		if (arch->cputype == CPU_TYPE_X86_64 || header->nfat_arch == 1)
			return (otool(s, s.ptr + arch->offset));
		arch = get_fat_arch_32(s, arch, header->magic, sizeof(struct fat_arch));
		if (!arch)
			return (ERR);
	}
	x86_64_not_found(s, ptr);
	return (OK);
}
