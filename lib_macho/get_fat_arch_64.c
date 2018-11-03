/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fat_arch_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:32:00 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:31:45 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct fat_arch_64		*get_fat_arch_64(t_stat stat, void *ptr, size_t offset)
{
	struct fat_arch_64	*arch;

	if (checkoff(stat, ptr, offset + sizeof(struct fat_arch_64)) == ERR)
		return (NULL);
	arch = (struct fat_arch_64 *)(ptr + offset);
	return (arch);
}
