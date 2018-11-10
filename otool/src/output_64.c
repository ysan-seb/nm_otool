/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:43:01 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 18:55:42 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int		output(t_stat stat, struct section_64 *sect, char *text)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < sect->size)
	{
		j = 0;
		printf("%016llx\t", sect->addr + i);
		while (i < sect->size && j < 16)
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

static void		print_header(struct mach_header_64 *h)
{
	printf("Mach Header\n");
	printf("      magic cputype cpusubtype  filetype ncmds sizeofcmds"
	"      flags\n");
	printf(" 0x%x %7u %10u  %8u %5u %10u 0x%08x\n", h->magic, h->cputype,
	(uint32_t)h->cpusubtype == 2147483651 ? 3 : h->cpusubtype,
	h->filetype, h->ncmds, h->sizeofcmds, h->flags);
}

int				output_64(t_stat st, struct mach_header_64 *h,
		struct segment_command_64 *seg)
{
	int					ret;
	struct section_64	*s;
	char				*text;

	ret = 0;
	s = get_section_64(st, (void*)(seg + 1), h->magic, 0);
	if (!s)
		return (ERR);
	if (strcmp(s->sectname, SECT_TEXT) != 0)
		return (OK);
	if (checkoff(st, h, s->offset + s->size) == ERR)
		return (ERR);
	if (strchr(st.opt, 't') && strlen(st.arch_name) == 0 && !st.object_name)
		printf("%s:\n", st.filename);
	else if (strchr(st.opt, 't') && strlen(st.arch_name) > 0)
		printf("%s %s:\n", st.filename, st.arch_name);
	strchr(st.opt, 't') ? printf("Contents of (%s,%s) section\n",
	s->segname, s->sectname) : 0;
	text = (void*)h + s->offset;
	if (strchr(st.opt, 't'))
		ret = output(st, s, text);
	if (strchr(st.opt, 'h'))
		print_header(h);
	return (ret);
}
