/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:25:15 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/08 15:48:33 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "lib_macho.h"

typedef struct			s_list64
{
	void				*ptr;
	int					stroff;
	char				*name;
	uint8_t				n_type;
	uint8_t				n_sect;
	uint16_t			n_desc;
	uint64_t			n_value;
	long				n_strx;
	struct s_list64		*next;
}						t_list64;

int						nm(t_stat stat, void *ptr);
int						handle_fat_32(t_stat s, void *ptr);
int						handle_32(t_stat stat, void *ptr);
int						handle_64(t_stat stat, void *ptr);
int						handle_archive(t_stat stat, void *ptr);
int						parse_section_32(t_stat *stat,
		struct mach_header *header, struct load_command *lc);
int						parse_section_64(t_stat *stat,
		struct mach_header_64 *header, struct load_command *lc);
struct nlist			*sort_ascii_32(t_stat stat,
		void *ptr, struct mach_header *header, struct symtab_command *s);
int						output32(t_stat stat,
		struct mach_header *h, struct symtab_command *s, void *p);
struct nlist_64			*sort_ascii_64(t_stat stat,
		void *ptr, struct mach_header_64 *header, struct symtab_command *s);
int						output64(t_stat stat,
		struct mach_header_64 *h, struct symtab_command *s, void *p);

#endif