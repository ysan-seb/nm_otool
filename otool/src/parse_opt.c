/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:59:28 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/10 17:51:35 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int		dup(t_stat *stat, char c)
{
	int i;

	i = 0;
	while (stat->opt[i])
	{
		if (stat->opt[i] == c)
		{
			printf("ft_otool : option -%c : may only "
			"occur zero or one times!\n", c);
			return (1);
		}
		i++;
	}
	return (0);
}

int				auth(char c)
{
	if (c == 't' || c == 'f' || c == 'h')
		return (1);
	return (0);
}

char			**err_null(char c)
{
	printf("ft_otool : invalid option -%c\n", c);
	return (NULL);
}

char			*set_opt(t_stat *stat, int i, int j, char *av)
{
	stat->opt[j] = av[i];
	av[0] = '\0';
	return (av);
}

char			**parse_opt(t_stat *s, char **a)
{
	int	i[4];

	memset(&i, 0, 4);
	while (a[++i[0]])
	{
		if (a[i[0]][0] == '-' && a[i[0]][1])
		{
			i[1] = 0;
			while (a[i[0]][++i[1]])
			{
				if (a[i[0]][1] == '-' && !a[i[0]][2] && !(a[i[0]][0] = '\0'))
					return (a + 1);
				else if (auth(a[i[0]][i[1]]) && !(i[3] = dup(s, a[i[0]][i[1]])))
					a[i[0]] = set_opt(s, i[1], i[2]++, a[i[0]]);
				else if (i[3])
					return (NULL);
				else
					return (err_null(a[i[0]][i[1]]));
			}
		}
		else if (a[i[0]][0] == '-' && !a[i[0]][1])
			return (err_null(0));
	}
	return (a + 1);
}
