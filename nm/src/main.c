/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:21:46 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/03 19:20:22 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int leave_the_program(char *file, char *error)
{
	if (!file)
		printf("%s\n", error);
	else
		printf("%s: %s\n", file, error);
	return (ERR);
}

static int arg_init(int ac, char *file)
{
	int fd;
	t_stat stat;

	stat.filename = file;
	stat.tss = 0;
	stat.dss = 0;
	stat.bss = 0;
	stat.m_arg = 0;
	if (ac > 2)
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

int main(int ac, char **av)
{
	int i;

	if (ac < 2)
		return (leave_the_program(NULL, "Usage: ft_nm <input file> ..."));
	i = 1;
	while (i < ac)
	{
		arg_init(ac, av[i]);
		i++;
	}
	return (OK);
}
