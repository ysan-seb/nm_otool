/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:43:01 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/10/31 15:22:17 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int		output(t_stat stat, struct mach_header_64 *header,
		struct section_64 *sect, char *text)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < swap_or_64(header->magic, sect->size))
	{
		j = 0;
		printf("%016llx\t", swap_or_64(header->magic, sect->addr) + i);
		while (i < swap_or_64(header->magic, sect->size) && j < 16)
		{
			if (strcmp(stat.arch_name, "(architecture ppc)") == 0)
			{
				printf("%02hhx", text[i]);
				if ((j + 1) % 4 == 0)
					printf(" ");
			}
			else
				printf("%02hhx ", text[i]);
			i++;
			j++;
		}
		printf("\n");
	}
	return (OK);
}

int				output_64(t_stat stat, struct mach_header_64 *header,
		struct segment_command_64 *seg)
{
	struct section_64	*sect;
	char				*text;

	sect = get_section_64(stat, (void*)(seg + 1), 0);
	if (!sect)
		return (ERR);
	if (strcmp(sect->sectname, SECT_TEXT) != 0)
		return (OK);
	if (checkoff(stat, header, swap_or_32(header->magic, sect->offset) +
				swap_or_64(header->magic, sect->size)) == ERR)
		return (ERR);
	if (strlen(stat.arch_name) == 0 && !stat.object_name)
		printf("%s:\n", stat.filename);
	else if (strlen(stat.arch_name) > 0)
		printf("%s %s:\n", stat.filename, stat.arch_name);
	else if (stat.object_name)
		printf("%s(%s):\n", stat.filename, stat.object_name);
	printf("Contents of (%s,%s) section\n", sect->segname, sect->sectname);
	text = (void*)header + swap_or_64(header->magic, sect->offset);
	return (output(stat, header, sect, text));
}
