/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:21:46 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/07 20:48:16 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int		leave_the_program(char *file, char *error)
{
	if (!file)
		printf("%s\n", error);
	else
		printf("%s: %s\n", file, error);
	return (ERR);
}

static int		arg_init(char *file)
{
	int			fd;
	t_stat		stat;

	stat.filename = file;
	if ((fd = open(file, O_RDONLY)) < 0) {
		fprintf(stderr, "%s%s%s\n", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump: '", file, "': No such file or directory");
		return (-1); }
		// return (leave_the_program(file, ERR_OPEN));
	if (fstat(fd, &stat.stat) < 0)
		return (leave_the_program("Error", ERR_STAT));
	if (((stat.stat.st_mode) & S_IFMT) == S_IFDIR){
		fprintf(stderr, "%s%s%s\n", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump: '", file, "': Is a directory");
		return (-1);
		}
	if ((stat.ptr = mmap(0, stat.stat.st_size,
					PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (leave_the_program(file, " is not an object file"));
	if (otool(stat, stat.ptr) == ERR)
		return (ERR);
	if (munmap(stat.ptr, stat.stat.st_size) < 0)
		return (leave_the_program("Error", ERR_MUNMAP));
	return (OK);
}

int				main(int ac, char **av)
{
	int		i;

	if (ac < 2)
		return (leave_the_program(NULL, "Usage: ft_otool <object file> ..."));
	i = 1;
	while (i < ac)
	{
		if (arg_init(av[i]) == ERR)
			return (ERR);
		i++;
	}
	return (OK);
}
