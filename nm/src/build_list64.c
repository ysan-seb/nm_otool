// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   build_list64.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2018/10/16 15:06:11 by ysan-seb          #+#    #+#             */
// /*   Updated: 2018/11/01 14:56:54 by ysan-seb         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "nm.h"

// static t_list64		*e_list64(struct nlist_64 e_64,
// 		struct mach_header_64 *header, void *ptr, int off)
// {
// 	t_list64 *elem;

// 	if (!(elem = (t_list64*)malloc(sizeof(t_list64))))
// 		return (NULL);
// 	elem->ptr = ptr;
// 	elem->stroff = off;
// 	elem->name = (ptr + off)
// 			+ swap_or_32(header->magic, e_64.n_un.n_strx);
// 	elem->n_type = e_64.n_type;
// 	elem->n_sect = e_64.n_sect;
// 	elem->n_desc = swap_or_16(header->magic, e_64.n_desc);
// 	elem->n_value = swap_or_64(header->magic, e_64.n_value);
// 	elem->n_strx = swap_or_32(header->magic, e_64.n_un.n_strx);
// 	elem->next = NULL;
// 	return (elem);
// }

// int					build_list64(t_stat stat,
// 		struct mach_header_64 *h, struct symtab_command *s, void *p)
// {
// 	int				i;
// 	char			*stringtable;
// 	struct nlist_64	*a;
// 	t_list64		*l;
// 	t_list64		*begin;

// 	if (checkoff(stat, p, swap_or_32(h->magic, s->symoff)) == ERR)
// 		return (ERR);
// 	a = (void*)p + swap_or_32(h->magic, s->symoff);
// 	if (checkoff(stat, p, swap_or_32(h->magic, s->stroff)) == ERR)
// 		return (ERR);
// 	stringtable = (void*)p + swap_or_32(h->magic, s->stroff);
// 	if (checkoff(stat, p, swap_or_32(h->magic, s->stroff) + swap_or_32(h->magic, a[0].n_un.n_strx)) == ERR)
// 		return (ERR);
// 	if (!(l = e_list64(a[0], h, p, swap_or_32(h->magic, s->stroff))))
// 		return (ERR);
// 	i = 0;
// 	begin = l;
// 	while (++i < (int)swap_or_32(h->magic, s->nsyms))
// 	{
// 		if (checkoff(stat, p, swap_or_32(h->magic, s->stroff) + swap_or_32(h->magic, a[i].n_un.n_strx)) == ERR || checkoff(stat, p, swap_or_32(h->magic, s->stroff)) == ERR)
// 			return (ERR);
// 		if (!(l->next = e_list64(a[i], h, p, swap_or_32(h->magic, s->stroff))))
// 			return (ERR);
// 		l = l->next;
// 	}
// 	begin = sort_list64(begin);
// 	return (output64(stat, begin));
// }
