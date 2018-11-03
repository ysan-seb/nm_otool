/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 15:21:11 by ysan-seb          #+#    #+#             */
/*   Updated: 2018/11/01 14:41:42 by ysan-seb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_list64		*with_begin(t_list64 *begin, t_list64 *list64)
{
	t_list64	*tmp1;
	t_list64	*tmp2;
	t_list64	*tmp3;

	tmp1 = list64;
	tmp2 = tmp1->next;
	tmp3 = tmp2->next;
	tmp1->next = tmp3;
	tmp2->next = tmp1;
	if (tmp1 == begin)
		begin = tmp2;
	return (begin);
}

static t_list64		*with_not_begin(t_list64 *begin, t_list64 *prev,
t_list64 *list64)
{
	t_list64	*tmp1;
	t_list64	*tmp2;
	t_list64	*tmp3;

	tmp1 = list64;
	tmp2 = tmp1->next;
	tmp3 = tmp2->next;
	prev->next = tmp2;
	tmp1->next = tmp3;
	tmp2->next = tmp1;
	return (begin);
}

t_list64			*sort_list64(t_list64 *list64)
{
	t_list64	*begin;
	t_list64	*tmp1;
	t_list64	*tmp2;
	t_list64	*tmp3;
	t_list64	*prev;

	begin = list64;
	while (list64->next)
	{
		tmp1 = list64;
		tmp2 = tmp1->next;
		tmp3 = tmp2->next;
		if (tmp1 == begin && strcmp(tmp1->name, tmp2->name) > 0)
		{
			list64 = with_begin(begin, list64);
			list64 = begin;
		}
		else if (tmp1 != begin && strcmp(tmp1->name, tmp2->name) > 0)
		{
			begin = with_not_begin(begin, prev, list64);
			list64 = begin;
		}
		else
		{
			prev = list64;
			list64 = list64->next;
		}
	}
	return (begin);
}
