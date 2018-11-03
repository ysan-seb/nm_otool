/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkoff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:18:37 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 13:40:52 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

int		checkoff(t_stat stat, void *ptr, size_t offset)
{
	if ((stat.ptr + stat.stat.st_size) < (ptr + offset))
	{
		printf("%s: \e[1;38;5;1mtruncated\e[0m or "
		"\e[1;38;5;1mmalformed\e[0m file\n", stat.filename);
		return (ERR);
	}
	return (OK);
}
