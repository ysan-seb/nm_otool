/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:16:17 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 16:20:39 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		checkptr(t_stat stat, char *str)
{
	int i;

	i = 0;
	(void)stat;
	while (str[i])
	{
		if (stat.ptr + stat.stat.st_size < (void*)(str + i + 2))
			return (i + 2);
		i++;
	}
	return (0);
}
