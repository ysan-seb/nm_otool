/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symtab_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:47:05 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/05 18:07:41 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_macho.h"

struct symtab_command	*get_symtab_command(
		t_stat stat, void *ptr, uint32_t magic, size_t offset)
{
	struct symtab_command	*symtab;

	if (checkoff(stat, ptr, offset + sizeof(struct symtab_command)) == ERR)
		return (NULL);
	symtab = (struct symtab_command *)(ptr + offset);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64)
		return (symtab);
	symtab->symoff = swap_bits_32(symtab->symoff);
	symtab->nsyms = swap_bits_32(symtab->nsyms);
	symtab->stroff = swap_bits_32(symtab->stroff);
	symtab->strsize = swap_bits_32(symtab->strsize);
	return (symtab);
}
