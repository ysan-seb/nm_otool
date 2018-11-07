/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:23:25 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 16:16:06 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void				swap_arr(struct nlist_64 *a, struct nlist_64 *b)
{
	struct nlist_64 c;

	c = *a;
	*a = *b;
	*b = c;
}

static int				is_sorted(void *ptr, struct nlist_64 *array,
	struct symtab_command *s)
{
	uint32_t	i;
	char		*stringtable;
	char		*s1;
	char		*s2;

	stringtable = (void *)ptr + s->stroff;
	i = 0;
	while (i + 1 < s->nsyms)
	{
		s1 = stringtable + array[i].n_un.n_strx;
		s2 = stringtable + array[i + 1].n_un.n_strx;
		if (strcmp(s1, s2) > 0)
			return (0);
		else if (strcmp(s1, s2) == 0)
			if (array[i].n_value > array[i + 1].n_value)
				return (0);
		i++;
	}
	return (1);
}

static struct nlist_64	*sort(void *ptr,
	struct nlist_64 *array, struct symtab_command *s)
{
	uint32_t		i;
	char			*s1;
	char			*s2;
	char			*stringtable;

	i = 0;
	stringtable = (void *)ptr + s->stroff;
	while (i + 1 < s->nsyms)
	{
		s1 = stringtable + array[i].n_un.n_strx;
		s2 = stringtable + array[i + 1].n_un.n_strx;
		if (strcmp(s1, s2) > 0)
			swap_arr(&array[i], &array[i + 1]);
		else if (strcmp(s1, s2) == 0)
			if (array[i].n_value > array[i + 1].n_value)
				swap_arr(&array[i], &array[i + 1]);
		i++;
	}
	return (array);
}

static struct nlist_64	*get_nlist(t_stat stat,
	struct mach_header_64 *h, struct symtab_command *s, void *ptr)
{
	uint32_t		i;
	struct nlist_64 *array;
	char			*stringtable;
	char			*str;

	if (checkoff(stat, ptr, s->symoff) == ERR ||
		checkoff(stat, ptr, s->stroff) == ERR ||
		checkoff(stat, ptr, s->strsize) == ERR)
		return (NULL);
	i = 0;
	array = (void *)ptr + s->symoff;
	stringtable = (void *)ptr + s->stroff;
	while (i < s->nsyms)
	{
		array[i].n_un.n_strx = swap_or_32(h->magic, array[i].n_un.n_strx);
		if (checkoff(stat, stringtable, array[i].n_un.n_strx) == ERR)
			return (NULL);
		str = stringtable + array[i].n_un.n_strx;
		if (checkoff(stat, str, checkptr(stat, str)) == ERR)
			return (NULL);
		array[i].n_desc = swap_or_16(h->magic, array[i].n_desc);
		array[i].n_value = swap_or_64(h->magic, array[i].n_value);
		i++;
	}
	return (array);
}

struct nlist_64			*sort_ascii_64(t_stat stat,
	void *ptr, struct mach_header_64 *header, struct symtab_command *s)
{
	struct nlist_64 *array;

	if (!(array = get_nlist(stat, header, s, ptr)))
		return (NULL);
	while (1)
	{
		if (!(array = sort(ptr, array, s)))
			return (NULL);
		if (is_sorted(ptr, array, s))
			break ;
	}
	return (array);
}
