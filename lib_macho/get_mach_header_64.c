/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mach_header_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:35:25 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:32:49 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct mach_header_64	*get_mach_header_64(
		t_stat stat, void *ptr, size_t offset)
{
	struct mach_header_64	*header;

	if (checkoff(stat, ptr, offset + sizeof(struct mach_header_64)) == ERR)
		return (NULL);
	header = (struct mach_header_64 *)(ptr + offset);
	return (header);
}
