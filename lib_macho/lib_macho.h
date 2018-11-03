/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_macho.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 13:47:31 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 20:19:07 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_MACHO_H
# define LIB_MACHO_H

# include <ar.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>

# define FAILED	((void *)-1 )
# define OK		0
# define NO		1
# define ERR	-1
# define ERR_OPEN	"No such file or directory"
# define ERR_STAT	"a problem was encountered with fstat"
# define ERR_MAP	"The file was \e[1;38;5;1mnot\e[0m recognized as a\e[1;38;5;1m valid object file\e[0m"
# define ERR_MUNMAP	"a problem was encountered with munmap"
# define NOT_VALID	"The file was \e[1;38;5;1mnot\e[0m recognized as a\e[1;38;5;1m valid object file\e[0m"

typedef struct				s_stat
{
	char					*filename;
	char					*object_name;
	char					arch_name[256];
	void					*ptr;
	int						m_arg;
	int						i_sect;
	int						tss;
	int						dss;
	int						bss;
	struct stat				stat;
}							t_stat;

int							checkoff(t_stat stat, void *ptr, size_t offset);
uint16_t					swap_or_16(uint32_t magic, uint16_t value);
uint32_t					swap_or_32(uint32_t magic, uint32_t value);
uint64_t					swap_or_64(uint32_t magic, uint64_t value);
struct mach_header			*get_mach_header_32(t_stat stat,
		void *ptr, size_t offset);
struct mach_header_64		*get_mach_header_64(t_stat stat,
		void *ptr, size_t offset);
struct fat_header			*get_fat_header(t_stat stat,
		void *ptr, size_t offset);
struct fat_arch				*get_fat_arch_32(t_stat stat,
		void *ptr, size_t offset);
struct fat_arch_64			*get_fat_arch_64(t_stat stat,
		void *ptr, size_t offset);
struct symtab_command		*get_symtab_command(t_stat stat,
		void *ptr, size_t offset);
struct load_command			*get_load_command(t_stat stat,
		void *ptr, size_t offset);
struct segment_command		*get_segment_command_32(t_stat stat,
		void *ptr, size_t offset);
struct segment_command_64	*get_segment_command_64(t_stat stat,
		void *ptr, size_t offset);
struct section				*get_section_32(t_stat stat,
		void *ptr, size_t offset);
struct section_64			*get_section_64(t_stat stat,
		void *ptr, size_t offset);

#endif
