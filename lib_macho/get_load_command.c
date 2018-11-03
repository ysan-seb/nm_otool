/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_load_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:34:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:32:24 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct load_command		*get_load_command(t_stat stat, void *ptr, size_t offset)
{
	struct load_command	*lc;

	if (checkoff(stat, ptr, offset + sizeof(struct load_command)) == ERR)
		return (NULL);
	lc = (struct load_command *)(ptr + offset);
	return (lc);
}
