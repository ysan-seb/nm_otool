/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:25:15 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/09 17:35:27 by ysan-seb         ###   ########.fr       */
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

char					**parse_opt(t_stat *stat, char **av);
int						nm(t_stat stat, void *ptr);
int						handle_fat_32(t_stat s, void *ptr);
int						handle_32(t_stat stat, void *ptr);
int						handle_64(t_stat stat, void *ptr);
int						handle_archive(t_stat stat, void *ptr);
int						parse_section_32(t_stat *stat,
		struct mach_header *header, struct load_command *lc);
int						parse_section_64(t_stat *stat,
		struct mach_header_64 *header, struct load_command *lc);
struct nlist			*sort_32(t_stat stat, void *ptr,
		struct mach_header *header, struct symtab_command *s);
struct nlist			*ascii_sort_32(void *ptr,
		struct nlist *array, struct symtab_command *s);
struct nlist			*reverse_ascii_sort_32(void *ptr,
		struct nlist *array, struct symtab_command *s);
struct nlist			*digit_sort_32(void *ptr,
		struct nlist *array, struct symtab_command *s);
struct nlist			*reverse_digit_sort_32(void *ptr,
		struct nlist *array, struct symtab_command *s);
int						output32(t_stat stat,
		struct mach_header *h, struct symtab_command *s, void *p);
struct nlist_64			*sort_64(t_stat stat,
		void *ptr, struct mach_header_64 *header, struct symtab_command *s);
struct nlist_64			*ascii_sort_64(void *ptr,
		struct nlist_64 *array, struct symtab_command *s);
struct nlist_64			*reverse_ascii_sort_64(void *ptr,
		struct nlist_64 *array, struct symtab_command *s);
struct nlist_64			*digit_sort_64(void *ptr,
		struct nlist_64 *array, struct symtab_command *s);
struct nlist_64			*reverse_digit_sort_64(void *ptr,
		struct nlist_64 *array, struct symtab_command *s);
int						output64(t_stat stat,
		struct mach_header_64 *h, struct symtab_command *s, void *p);
int						checkptr(t_stat stat, char *str);

#endif
