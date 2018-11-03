/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mach_header_32.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:34:53 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:32:40 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct mach_header	*get_mach_header_32(t_stat stat, void *ptr, size_t offset)
{
	struct mach_header	*header;

	if (checkoff(stat, ptr, offset + sizeof(struct mach_header)) == ERR)
		return (NULL);
	header = (struct mach_header *)(ptr + offset);
	return (header);
}
