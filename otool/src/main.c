/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:21:46 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 18:46:42 by ysan-seb         ###   ########.fr       */
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

static int		arg_init(t_stat stat, char *file)
{
	int			fd;

	stat.filename = file;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (leave_the_program(file, ERR_OPEN));
	if (fstat(fd, &stat.stat) < 0)
		return (leave_the_program("Error", ERR_STAT));
	if (((stat.stat.st_mode) & S_IFMT) == S_IFDIR)
		return (leave_the_program(file, "': Is a directory"));
	if ((stat.ptr = mmap(0, stat.stat.st_size,
					PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (leave_the_program(file, " is not an object file"));
	if (otool(stat, stat.ptr) == ERR)
		return (ERR);
	if (munmap(stat.ptr, stat.stat.st_size) < 0)
		return (leave_the_program("Error", ERR_MUNMAP));
	return (OK);
}

static int		nb_file(char **av)
{
	int i;
	int nb_file;
	int nb_opt;

	i = 0;
	nb_file = 0;
	nb_opt = 0;
	while (av[i])
	{
		if (av[i][0])
			nb_file++;
		if (!av[i][0] && av[i][1])
			nb_opt++;
		i++;
	}
	if (nb_file && !nb_opt)
		return (0);
	return (nb_file);
}

int				main(int ac, char **av)
{
	int		i;
	t_stat	stat;

	stat.opt[0] = 0;
	i = -1;
	if ((av = parse_opt(&stat, av)) == NULL)
		return (leave_the_program(NULL, "Usage: [options] ft_otool"
		" <input file> ...\n\t-f     Display the universal headers.\n\t"
		"-h     Display the Mach header.\n\t"
		"-t     Display the contents of the (__TEXT,__text) section."));
	ac = nb_file(av);
	if (ac == 0)
		return (leave_the_program(NULL, "Usage: [options] ft_otool "
		"<input file> ...\n\t-f     Display the universal headers.\n\t"
		"-h     Display the Mach header.\n\t"
		"-t     Display the contents of the (__TEXT,__text) section."));
	while (av[++i])
	{
		if (av[i][0] != '\0')
			arg_init(stat, av[i]);
	}
	return (OK);
}
