/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:14:58 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 19:59:18 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int get_symbole_type(t_stat stat, struct nlist_64 e64)
{
	char type = e64.n_type & N_TYPE;
	char s_type = '?';

	if (type == N_ABS)
		s_type = 'a';
	else if (type == N_INDR)
		s_type = 'i';
	else if (type == N_UNDF || type == N_PBUD)
		s_type = 'u';
	if (type == N_SECT)
	{
		if (e64.n_sect == stat.tss)
			s_type = 't';
		else if (e64.n_sect == stat.dss)
			s_type = 'd';
		else if (e64.n_sect == stat.bss)
			s_type = 'b';
		else
			s_type = 's';
	}
	if (e64.n_type & N_EXT)
		s_type -= 32;
	return (s_type);

}

static void print_name(t_stat stat)
{
	if (stat.m_arg)
		printf("\n%s:\n", stat.filename);
	else if (strlen(stat.arch_name) > 0)
		printf("\n%s %s:\n", stat.filename, stat.arch_name);
	else if (stat.object_name)
		printf("\n%s(%s):\n", stat.filename, stat.object_name);
}

void swap_arr(struct nlist_64 *a, struct nlist_64 *b)
{
	struct nlist_64 c;

	c = *a;
	*a = *b;
	*b = c;
}

int		is_sorted(void *ptr, struct nlist_64 *array, struct mach_header_64 *h, struct symtab_command *s)
{
	uint32_t i;
	char *stringtable;
	char *s1;
	char *s2;

	stringtable = (void *)ptr + s->stroff;
	i = 0;
	while (i + 1 < s->nsyms)
	{
		s1 = stringtable + swap_or_32(h->magic, array[i].n_un.n_strx);
		s2 = stringtable + swap_or_32(h->magic, array[i + 1].n_un.n_strx);
		if (strcmp(s1, s2) > 0)
			return (0);
		else if (strcmp(s1, s2) == 0)
			if (array[i].n_value > array[i + 1].n_value)
				return (0);
		i++;
	}
	return (1);
}

struct nlist_64 *sort(t_stat stat, void *ptr, struct mach_header_64 *header, struct symtab_command *s)
{
	uint32_t i;
	struct nlist_64 *array;
	char *stringtable;
	char *s1;
	char *s2;

	i = 0;
	if (checkoff(stat, ptr, s->symoff) == ERR || checkoff(stat, ptr, s->stroff) == ERR || checkoff(stat, ptr, s->strsize) == ERR)
		return (NULL);
	array = (void *)ptr + s->symoff;
	stringtable = (void *)ptr + s->stroff;
	while (i + 1 < s->nsyms)
	{
		if (checkoff(stat, stringtable,  swap_or_32(header->magic, array[i].n_un.n_strx)) == ERR || checkoff(stat, stringtable, swap_or_32(header->magic, array[i + 1].n_un.n_strx)) == ERR)
			return (NULL);
		s1 = stringtable + swap_or_32(header->magic, array[i].n_un.n_strx);
		s2 = stringtable + swap_or_32(header->magic, array[i + 1].n_un.n_strx);
		if (strcmp(s1, s2) > 0)
			swap_arr(&array[i], &array[i + 1]);
		else if (strcmp(s1, s2) == 0)
		{
			if (array[i].n_value > array[i + 1].n_value)
				swap_arr(&array[i], &array[i + 1]);
		}
		i++;
	}
	return (array);
}

struct nlist_64 *sort_ascii(t_stat stat, void *ptr, struct mach_header_64 *header, struct symtab_command *s){
	struct nlist_64 *array;

	while (1)
	{
		if (!(array = sort(stat, ptr, header, s)))
			return (NULL);
		if (is_sorted(ptr, array, header, s))
			break;
	}
	return (array);
}

int output64(t_stat stat,
			 struct mach_header_64 *h, struct symtab_command *s, void *p)
{
	uint32_t i;
	struct nlist_64 *a;
	char *stringtables;

	if ((a = sort_ascii(stat, p, h, s)) == NULL || checkoff(stat, p, s->stroff) == ERR)
		return (ERR);
	stringtables = p + s->stroff;
	i = 0;
	print_name(stat);
	while (i < s->nsyms)
	{
		if (a[i].n_type & N_STAB)
			;
		else 
		{
			if (a[i].n_type & N_SECT)
				printf("%016llx %c %s\n", a[i].n_value, get_symbole_type(stat, a[i]), stringtables + a[i].n_un.n_strx);
			else
				printf("                 %c %s\n", get_symbole_type(stat, a[i]), stringtables + a[i].n_un.n_strx);
		}
		i++;
	}
	return (OK);
}