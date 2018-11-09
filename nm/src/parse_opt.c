/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:59:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/09 17:44:24 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		check_double(t_stat *stat, char c)
{
	int i;

	i = 0;
	while (stat->opt[i])
	{
		if (stat->opt[i] == c)
		{
			printf("ft_nm : option -%c : may only "
			"occur zero or one times!\n", c);
			return (1);
		}
		i++;
	}
	return (0);
}

int				authorized_option(char c)
{
	if (c == 'j' || c == 'n' || c == 'p' || c == 'r')
		return (1);
	return (0);
}

char			**parse_opt(t_stat *stat, char **av)
{
	int	i;
	int j;
	int k;
	int ret;

	i = 1;
	k = 0;
	ret = 0;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1])
		{
			j = 1;
			while (av[i][j])
			{
				if (av[i][0] == '-' && av[i][1] == '-')
				{
					av[i][0] = '\0';
					return (av + 1);
				}
				else if (authorized_option(av[i][j]) && !(ret = check_double(stat, av[i][j])))
				{
					stat->opt[k++] = av[i][j];
					av[i][0] = '\0';
				}
				else if (ret)
					return (NULL);
				else
				{
					printf("ft_nm : invalid option -%c\n", av[i][j]);
					return (NULL);
				}
				j++;
			}
		}
		else if (av[i][0] == '-' && !av[i][1])
		{
			printf("ft_nm : invalid option -\n");
			return (NULL);
		}
		i++;
	}
	return (av + 1);
}
