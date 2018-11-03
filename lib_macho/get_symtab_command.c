/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symtab_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:47:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 18:34:04 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct symtab_command	*get_symtab_command(
		t_stat stat, void *ptr, size_t offset)
{
	struct symtab_command	*symtab;

	if (checkoff(stat, ptr, offset + sizeof(struct symtab_command)) == ERR)
		return (NULL);
	symtab = (struct symtab_command *)(ptr + offset);
	return (symtab);
}
