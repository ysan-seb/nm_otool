/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:32:54 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/09 17:38:26 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void			swap_arr(struct nlist *a, struct nlist *b)
{
	struct nlist c;

	c = *a;
	*a = *b;
	*b = c;
}

static int			is_sorted(void *ptr,
		struct nlist *array, struct symtab_command *s)
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

static struct nlist	*sort_ascii_32(void *ptr,
		struct nlist *array, struct symtab_command *s)
{
	uint32_t	i;
	char		*s1;
	char		*s2;
	char		*stringtable;

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

struct nlist		*ascii_sort_32(void *ptr,
		struct nlist *array, struct symtab_command *s)
{
	while (1)
	{
		if (!(array = sort_ascii_32(ptr, array, s)))
			return (NULL);
		if (is_sorted(ptr, array, s))
			break ;
	}
	return (array);
}
