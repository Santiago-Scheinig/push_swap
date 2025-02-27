/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/27 19:51:01 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_mergepair(t_list *src, t_list *des, int run_a, int run_b)
{
	t_list	*src_last;
	t_list	*des_last;
	int		order;

	order = RRB_ORDER;
	src_last = ft_lstlast(src);
	des_last = ft_lstlast(des);
	if (src->run == run_a || src->run == run_b)
	{
		if ((src->run != run_a || src->run != run_b) 
		&& (src_last->run == run_a || src_last->run == run_a))
			return (RRB_ORDER);
		if (*(src->content) < *(src_last->content) && 
		(src_last->run == run_a || src_last->run == run_b))
			order = RRB_ORDER;
		else if (*(src->content) < *(des->content))
			order = PA_ORDER;
		else if (*(src->content) > *(des_last->content))
			order = PA_ORDER;
		if (order == PA_ORDER && *(des_last->content) > *(src->content))
			if (*(des->content) > *(des_last->content))
				order = RRA_ORDER;
	}
	return (order);
}

void	ft_mergesort(t_list **stacks, char **order_lst, int rlen)
{
	int	limit;
	int	order;
	int	run_a;
	int run_b;

	if (rlen)
		rlen = 0;
	while (stacks[1])
	{
		run_a = stacks[1]->run;
		run_b = ft_lstlast(stacks[1])->run;
		limit = *(ft_lstlast(stacks[1])->content);
		if (limit < *(stacks[1]->content))
			limit = *(stacks[1]->content);
		if ((limit < *(ft_limitchr(stacks[0], -1, 1)->content)))
			while (*(stacks[0]->content) < limit)
				if (ft_execute(RA_ORDER, stacks))
					ft_printf("%s\n", order_lst[RA_ORDER]);
		while (ft_runsize(stacks[1], run_a) || ft_runsize(stacks[1], run_b))
		{
			order = ft_mergepair(stacks[1], stacks[0], run_a, run_b);
			if (ft_execute(order, stacks))
				ft_printf("%s\n", order_lst[order]);
		}
	}
}
