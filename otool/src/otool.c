/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:23:47 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 18:44:04 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		otool(t_stat stat, void *ptr)
{
	int				ret;
	unsigned int	magic;

	ret = OK;
	magic = *(int*)ptr;
	if (magic == 0)
		return (ERR);
	if (magic == MH_MAGIC || magic == MH_CIGAM)
		ret = handle_32(stat, ptr);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		ret = handle_64(stat, ptr);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		ret = handle_fat_32(stat, ptr);
	else if (checkoff(stat, ptr, 8) == OK && strncmp(ptr, ARMAG, SARMAG) == OK)
		ret = handle_archive(stat, ptr);
	else
	{
		printf("%s: %s\n", stat.filename, "is not an object file");
		return (ERR);
	}
	return (ret);
}
