/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:34:49 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 18:14:30 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int		object_parse(t_stat s, void *ptr, size_t off)
{
	void					*h_ptr;
	struct ar_hdr			*o;

	printf("Archive : %s\n", s.filename);
	while (1)
	{
		if (s.ptr + s.stat.st_size < ptr + off + 1)
			break ;
		o = ptr + off;
		off += sizeof(struct ar_hdr);
		if (strncmp(o->ar_name, ARMAG, SARMAG) == OK)
			break ;
		if (s.ptr + s.stat.st_size < ptr + off + atoi(o->ar_name))
			break ;
		h_ptr = ptr + off + atoi(o->ar_name + 3);
		s.object_name = o->ar_fmag + 2;
		off += atoi(o->ar_size);
		strchr(s.opt, 't') ? printf("%s(%s):\n", s.filename, s.object_name) : 0;
		if (otool(s, h_ptr) == ERR)
			return (ERR);
	}
	return (OK);
}

int				handle_archive(t_stat stat, void *ptr)
{
	size_t			offset;
	struct ar_hdr	*symtab_header;

	offset = SARMAG;
	if (checkoff(stat, ptr, offset) == ERR)
		return (ERR);
	symtab_header = ptr + offset;
	offset += sizeof(struct ar_hdr);
	if (checkoff(stat, ptr, atoi(symtab_header->ar_size) + offset) == ERR)
		return (ERR);
	offset += atoi(symtab_header->ar_size);
	if (checkoff(stat, ptr, offset) == ERR)
		return (ERR);
	if (object_parse(stat, ptr, offset) == ERR)
		return (ERR);
	return (OK);
}
