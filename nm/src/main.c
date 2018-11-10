/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:21:46 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 17:37:41 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	leave_the_program(char *file, char *error)
{
	if (!file)
		fprintf(stderr, "%s\n", error);
	else
		fprintf(stderr, "%s: %s\n", file, error);
	return (ERR);
}

static int	arg_init(t_stat stat, int nb_file, char *file)
{
	int		fd;

	stat.filename = file;
	stat.tss = 0;
	stat.dss = 0;
	stat.bss = 0;
	stat.m_arg = 0;
	if (nb_file > 1)
		stat.m_arg = 1;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (leave_the_program(file, ERR_OPEN));
	if (fstat(fd, &stat.stat) < 0)
		return (leave_the_program("Error", ERR_STAT));
	if ((stat.ptr = mmap(0, stat.stat.st_size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (leave_the_program(file, ERR_MAP));
	nm(stat, stat.ptr);
	if (munmap(stat.ptr, stat.stat.st_size) < 0)
		return (leave_the_program("Error", ERR_MUNMAP));
	return (OK);
}

static int	nb_file(char **av)
{
	int i;
	int nb_file;

	i = 0;
	nb_file = 0;
	while (av[i])
	{
		if (av[i][0])
			nb_file++;
		i++;
	}
	return (nb_file);
}

int			main(int ac, char **av)
{
	int		i;
	t_stat	stat;

	stat.opt[0] = 0;
	i = -1;
	if ((av = parse_opt(&stat, av)) == NULL)
		return (leave_the_program(NULL, "Usage: [options] ft_nm "
		"<input file> ...\n\t-j\tJust display the symbol names "
		"(no value or type).\n\t-n\tSort numerically rather than alphabetically"
		".\n\t-p\tDon't sort; display in symbol-table order.\n\t"
		"-r\tSort in reverse order."));
	ac = nb_file(av);
	if (ac == 0)
		return (arg_init(stat, 1, "a.out"));
	while (av[++i])
	{
		if (av[i][0] != '\0')
			arg_init(stat, ac, av[i]);
	}
	return (OK);
}
