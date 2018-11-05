/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:34:49 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 20:58:00 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


static int		get_size(t_stat stat, void *ptr, size_t offset)
{
	uint32_t		*size;

	size = NULL;
	if (checkoff(stat, ptr, offset) == ERR)
		return (ERR);
	size = stat.ptr + offset;
	return (*size / 8);
}

static int		object_exist(uint32_t elem, uint32_t *object, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		if (elem == object[i])
			return (1);
		i++;
	}
	return (0);
}

static int		get_n_object(t_stat s, void *p, size_t off)
{
	int			i;
	int			size;
	uint32_t	*elem;
	uint32_t	*object;
	uint32_t	n_object;

	if ((size = get_size(s, p, off)) == ERR || checkoff(s, p, size * 8) == ERR)
		return (ERR);
	p += off + 8;
	n_object = 0;
	if (!(object = (uint32_t*)malloc(sizeof(uint32_t) * size)))
		return (ERR);
	i = 0;
	while (i < size)
	{
		elem = p;
		if (!object_exist(*elem, object, size))
		{
			object[n_object] = *elem;
			n_object++;
		}
		p += 8;
		i++;
	}
	free(object);
	return (n_object);
}

static int		object_parse(t_stat s, struct ar_hdr *o, int size, size_t off)
{
	void					*header;

	if (checkoff(s, s.ptr, off + atoi(o->ar_name)) == ERR)
		return (ERR);
	header = s.ptr + off + atoi(o->ar_name + 3);
	s.object_name = o->ar_fmag + 2;
	while (size--)
	{
		if (nm(s, header) == ERR)
			return (ERR);
		if (size > 0)
		{
			off += atoi(o->ar_size);
			if (checkoff(s, s.ptr, off) == ERR)
				return (ERR);
			o = s.ptr + off;
			s.object_name = o->ar_fmag + 2;
			off += sizeof(struct ar_hdr);
			if (checkoff(s, s.ptr, off + atoi(o->ar_name)) == ERR)
				return (ERR);
			header = s.ptr + off + atoi(o->ar_name + 3);
		}
	}
	return (OK);
}

int				handle_archive(t_stat stat, void *ptr)
{
	int				size;
	size_t			offset;
	struct ar_hdr	*symtab_header;
	struct ar_hdr	*object_header;

	offset = SARMAG;
	if (checkoff(stat, ptr, offset) == ERR)
		return (ERR);
	symtab_header = ptr + offset;
	offset += sizeof(struct ar_hdr);
	if ((size = get_n_object(stat, ptr, offset
					+ atoi(symtab_header->ar_name + 3))) == ERR)
		return (ERR);
	if (checkoff(stat, ptr, atoi(symtab_header->ar_size) + offset) == ERR)
		return (ERR);
	offset += atoi(symtab_header->ar_size);
	if (checkoff(stat, ptr, offset) == ERR)
		return (ERR);
	object_header = stat.ptr + offset;
	offset += sizeof(struct ar_hdr);
	if (object_parse(stat, object_header, size, offset) == ERR)
		return (ERR);
	return (OK);
}
