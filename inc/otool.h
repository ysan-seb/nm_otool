/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:25:15 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 16:38:55 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "lib_macho.h"

int							otool(t_stat stat, void *ptr);
char						**parse_opt(t_stat *s, char **a);
int							handle_fat_32(t_stat stat, void *ptr);
int							handle_32(t_stat stat, void *ptr);
int							handle_64(t_stat stat, void *ptr);
int							handle_archive(t_stat stat, void *ptr);
int							parse_segment_32(t_stat stat,
		struct mach_header *header, struct load_command *lc);
int							parse_segment_64(t_stat stat,
		struct mach_header_64 *header, struct load_command *lc);
int							output_32(t_stat stat,
		struct mach_header *header, struct segment_command *seg);
int							output_64(t_stat stat,
		struct mach_header_64 *header, struct segment_command_64 *seg);

#endif
