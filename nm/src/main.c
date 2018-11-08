/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:21:46 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/08 17:49:41 by ysan-seb         ###   ########.fr       */
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

static int	arg_init(int ac, char *file)
{
	int		fd;
	t_stat	stat;

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

int			check_double(char opt[5], char c)
{
	int i;

	i = 0;
	while (opt[i])
	{
		if (opt[i] == c)
		{
			printf("ft_nm : option -%c : may only "
			"occur zero or one times!\n", c);
			return (1);
		}
		i++;
	}
	return (0);
}

int			parse_opt(char **av)
{
	int		i;
	int		j;
	int		k;
	char	opt[5];

	i = 0;
	k = 0;
	opt[4] = 0;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1])
		{
			j = 1;
			while (av[i][j])
			{
				if ((av[i][j] == 'j' || av[i][j] == 'n' || av[i][j] == 'p' ||
				av[i][j] == 'r') && !check_double(opt, av[i][j]))
					opt[k++] = av[i][j];
				else
				{
					printf("ft_nm : invalid option -%c\n",  av[i][j]);
					return (ERR);
				}
				j++;
			}
		}
		else if (av[i][0] == '-' && !av[i][1])
			return(leave_the_program(NULL, "ft_nm : Tinvalid option -"));
		i++;
	}
	return (OK);
}

int			main(int ac, char **av)
{
	int i;

	if (ac < 2)
		return (leave_the_program(NULL, "Usage: ft_nm <input file> ...\n\t-j\t"
		"Just display the symbol names (no value or type).\n\t-n\t"
		"Sort numerically rather than alphabetically.\n\t-p\tDon't" 
		"sort; display in symbol-table order.\n\t-r\tSort in reverse order."));
	i = 1;
	if (parse_opt(av + 1) == ERR)
		return (leave_the_program(NULL, "Usage: ft_nm <input file> ...\n\t-j"
		"\tJust display the symbol names "
		"(no value or type).\n\t-n\tSort numerically rather than alphabetically"
		".\n\t-p\tDon't sort; display in symbol-table order.\n\t"
		"-r\tSort in reverse order."));
	while (i < ac)
	{
		if (av[i][0] == '!')
			arg_init(ac, av[i]);
		i++;
	}
	return (OK);
}
