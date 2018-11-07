/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:14:58 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 15:57:55 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		get_sect_symbole_type(t_stat stat, struct nlist_64 e64)
{
	if (e64.n_sect == stat.tss)
		return ('t');
	else if (e64.n_sect == stat.dss)
		return ('d');
	else if (e64.n_sect == stat.bss)
		return ('b');
	else
		return ('s');
}

static int		get_symbole_type(t_stat stat,
struct mach_header_64 *header, struct nlist_64 e64)
{
	char type;
	char s_type;

	type = e64.n_type & N_TYPE;
	s_type = '?';
	if (header->filetype == MH_OBJECT
	&& e64.n_type & N_EXT && type == N_UNDF && e64.n_value > 0)
		return ('C');
	else if (type == N_ABS)
		s_type = 'a';
	else if (type == N_INDR)
		s_type = 'i';
	else if (type == N_UNDF || type == N_PBUD)
		s_type = 'u';
	else if (type == N_SECT)
		s_type = get_sect_symbole_type(stat, e64);
	if (e64.n_type & N_EXT)
		s_type -= 32;
	return (s_type);
}

static void		print_name(t_stat stat)
{
	if (stat.m_arg)
		printf("\n%s:\n", stat.filename);
	else if (strlen(stat.arch_name) > 0)
		printf("\n%s %s:\n", stat.filename, stat.arch_name);
}

static int		is_common_sym(struct mach_header_64 *h, struct nlist_64 a)
{
	if (h->filetype == MH_OBJECT && (a.n_type & N_TYPE) == N_UNDF
		&& a.n_type & N_EXT && a.n_value > 0)
		return (1);
	return (0);
}

int				output64(t_stat stat,
		struct mach_header_64 *h, struct symtab_command *s, void *p)
{
	uint32_t		i;
	struct nlist_64 *a;
	char			*stable;

	if ((a = sort_ascii_64(stat, p, h, s)) == NULL ||
	checkoff(stat, p, s->stroff) == ERR)
		return (ERR);
	stable = p + s->stroff;
	i = 0;
	print_name(stat);
	while (i < s->nsyms)
	{
		if (a[i].n_type & N_STAB)
			;
		else if (a[i].n_type & N_SECT || is_common_sym(h, a[i]))
			printf("%016llx %c %s\n", a[i].n_value,
			get_symbole_type(stat, h, a[i]), stable + a[i].n_un.n_strx);
		else
			printf("                 %c %s\n",
			get_symbole_type(stat, h, a[i]), stable + a[i].n_un.n_strx);
		i++;
	}
	return (OK);
}
