/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:36:29 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:33:05 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct section	*get_section_32(t_stat stat, void *ptr, size_t offset)
{
	struct section	*section;

	if (checkoff(stat, ptr, offset + sizeof(struct section)) == ERR)
		return (NULL);
	section = (struct section *)(ptr + offset);
	return (section);
}
