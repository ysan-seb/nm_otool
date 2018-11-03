/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:03:21 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 19:34:13 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int get_symbole_type(t_stat stat, struct nlist e32)
{
	char type = e32.n_type & N_TYPE;
	char s_type = '?';

	if (type == N_ABS)
		s_type = 'a';
	else if (type == N_INDR)
		s_type = 'i';
	else if (type == N_UNDF || type == N_PBUD)
		s_type = 'u';
	if (type == N_SECT)
	{
		if (e32.n_sect == stat.tss)
			s_type = 't';
		else if (e32.n_sect == stat.dss)
			s_type = 'd';
		else if (e32.n_sect == stat.bss)
			s_type = 'b';
		else
			s_type = 's';
	}
	if (e32.n_type & N_EXT)
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

static void swap_arr(struct nlist *a, struct nlist *b)
{
	struct nlist c;

	c = *a;
	*a = *b;
	*b = c;
}

static int		is_sorted(void *ptr, struct nlist *array, struct mach_header *h, struct symtab_command *s)
{
	uint32_t i;
	char *stringtable;
	char *s1;
	char *s2;

	stringtable = (void *)ptr + swap_or_32(h->magic, s->stroff);
	i = 0;
	while (i + 1 < swap_or_32(h->magic, s->nsyms))
	{
		s1 = stringtable + swap_or_32(h->magic, array[i].n_un.n_strx);
		s2 = stringtable + swap_or_32(h->magic, array[i + 1].n_un.n_strx);
		if (strcmp(s1, s2) > 0)
			return (0);
		i++;
	}
	return (1);
}

static struct nlist *sort(t_stat stat, void *ptr, struct mach_header *header, struct symtab_command *s)
{
	uint32_t i;
	struct nlist *array;
	char *stringtable;
	char *s1;
	char *s2;
	// static int yolo = 0;
		(void)stat;
	// yolo++;
	i = 0;
	if (checkoff(stat, ptr, swap_or_32(header->magic, s->symoff)) == ERR || checkoff(stat, ptr, swap_or_32(header->magic, s->stroff)) == ERR || checkoff(stat, ptr, swap_or_32(header->magic, s->strsize)) == ERR)
		return (NULL);
	array = (void *)ptr + swap_or_32(header->magic, s->symoff);
	stringtable = (void *)ptr + swap_or_32(header->magic, s->stroff);
	while (i + 1 < swap_or_32(header->magic, s->nsyms))
	{
		if (checkoff(stat, stringtable,  swap_or_32(header->magic, array[i].n_un.n_strx)) == ERR || checkoff(stat, stringtable, swap_or_32(header->magic, array[i + 1].n_un.n_strx)) == ERR)
			return (NULL);
		s1 = stringtable + swap_or_32(header->magic, array[i].n_un.n_strx);
		s2 = stringtable + swap_or_32(header->magic, array[i + 1].n_un.n_strx);
		if (strcmp(s1, s2) > 0)
			swap_arr(&array[i], &array[i + 1]);
		else if (strcmp(s1, s2) == 0)
		{
			if (swap_or_32(header->magic, array[i].n_value) > swap_or_32(header->magic, array[i + 1].n_value))
				swap_arr(&array[i], &array[i + 1]);
		}
		i++;
	}
	return (array);
}

static struct nlist *sort_ascii(t_stat stat, void *ptr, struct mach_header *header, struct symtab_command *s){
	struct nlist *array;

	while (1)
	{
		if (!(array = sort(stat, ptr, header, s)))
			return (NULL);
		if (is_sorted(ptr, array, header, s))
			break;
	}
	return (array);
}

int output32(t_stat stat,
			 struct mach_header *h, struct symtab_command *s, void *p)
{
	uint32_t i;
	struct nlist *a;
	char *stringtables;


	if ((a = sort_ascii(stat, p, h, s)) == NULL || checkoff(stat, p, swap_or_32(h->magic, s->stroff)) == ERR)
		return (ERR);
	stringtables = p + swap_or_32(h->magic, s->stroff);
	i = 0;
	print_name(stat);
	while (i < swap_or_32(h->magic, s->nsyms))
	{
		if (a[i].n_type & N_STAB)
			;
		else 
		{
			if (a[i].n_type & N_SECT)
				printf("%08x %c %s\n", swap_or_32(h->magic, a[i].n_value), get_symbole_type(stat, a[i]), stringtables + swap_or_32(h->magic, a[i].n_un.n_strx));
			else
				printf("         %c %s\n", get_symbole_type(stat, a[i]), stringtables + swap_or_32(h->magic, a[i].n_un.n_strx));
		}
		i++;
	}
	return (OK);
}

// int					output32(t_stat stat, t_list64 *list64)
// {
// 	t_list64	*begin;
// 	char		*stringtables;

// 	if (!list64)
// 		return (ERR);
// 	begin = list64;
// 	if (checkoff(stat, list64->ptr, list64->stroff) == ERR)
// 		return (ERR);
// 	stringtables = list64->ptr + list64->stroff;
// 	print_name(stat);
// 	while (list64)
// 	{
// 		if (list64->n_type < 36)
// 		{
// 			if (list64->n_value != 0)
// 				printf("%08llx %c %s\n", list64->n_value,
// 				get_symbole_type(stat, list64), list64->name);
// 			else
// 				printf("         %c %s\n",
// 				get_symbole_type(stat, list64), list64->name);
// 		}
// 		list64 = list64->next;
// 	}
// 	// free_list64(begin);
// 	return (OK);
// }
