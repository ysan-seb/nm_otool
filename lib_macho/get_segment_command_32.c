/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_segment_command_32.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:38:00 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:33:36 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct segment_command	*get_segment_command_32(
		t_stat stat, void *ptr, size_t offset)
{
	struct segment_command	*segment;

	if (checkoff(stat, ptr, offset + sizeof(struct segment_command)) == ERR)
		return (NULL);
	segment = (struct segment_command *)(ptr + offset);
	return (segment);
}
