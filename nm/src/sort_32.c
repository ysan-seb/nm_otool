/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:17:42 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/09 17:38:47 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static struct nlist	*get_nlist(t_stat stat,
		struct mach_header *h, struct symtab_command *s, void *ptr)
{
	uint32_t		i;
	struct nlist	*array;
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
		array[i].n_value = swap_or_32(h->magic, array[i].n_value);
		i++;
	}
	return (array);
}

struct nlist		*sort_32(t_stat stat,
		void *ptr, struct mach_header *header, struct symtab_command *s)
{
	struct nlist *array;

	if (!(array = get_nlist(stat, header, s, ptr)))
		return (NULL);
	if (strchr(stat.opt, 'p'))
		return (array);
	if (strchr(stat.opt, 'r'))
	{
		if (strchr(stat.opt, 'n'))
			return (array = reverse_digit_sort_32(ptr, array, s));
		else
			return (array = reverse_ascii_sort_32(ptr, array, s));
	}
	if (strchr(stat.opt, 'n'))
		return (array = digit_sort_32(ptr, array, s));
	else
		return (array = ascii_sort_32(ptr, array, s));
}
