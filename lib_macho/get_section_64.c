/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:37:01 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:33:19 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct section_64	*get_section_64(t_stat stat, void *ptr, size_t offset)
{
	struct section_64	*section;

	if (checkoff(stat, ptr, offset + sizeof(struct section_64)) == ERR)
		return (NULL);
	section = (struct section_64 *)(ptr + offset);
	return (section);
}
