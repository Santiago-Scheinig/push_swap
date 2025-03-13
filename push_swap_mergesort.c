/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/13 21:19:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_mergepair(t_list *src, t_list *des, int run_a, int run_b)
{
	t_list	*src_last;
	t_list	*des_last;
	int		order;

	src_last = ft_lstlast(src);
	des_last = ft_lstlast(des);
	order = NO_ORDER;
	if ((src_last->run == run_a || src_last->run == run_b) && run_a != run_b)
	{
		if (src->run != run_a && src->run != run_b)
			order = RRB_ORDER;
		else if (*(src->content) < *(src_last->content))
			order = RRB_ORDER;
	}
	if (order == RRB_ORDER && (src_last->run == run_a || src_last->run == run_b) 
	&& *(des_last->content) > *(src_last->content))
		if (*(des->content) > *(des_last->content))
			order = RRR_ORDER;
	if (order == NO_ORDER)
	{
		order = PA_ORDER;
		if (*(des_last->content) > *(src->content))
			order = RRA_ORDER;
	}
	return (order);
}

static int ft_des_position(t_list **stacks, int run)
{
	int		order;
	int		des_max;
	int		des_min;
	int 	src_limit;

	src_limit = *(ft_limitchr(stacks[1], run, 1)->content);
	if (run >= 0 && src_limit < *(ft_limitchr(stacks[1], run + 1, 1)->content))
		src_limit = *(ft_limitchr(stacks[1], run + 1, 1)->content);
	des_min = *(ft_limitchr(stacks[0], -1, -1)->content);
	des_max = *(ft_limitchr(stacks[0], -1, 1)->content);
	if (src_limit > des_max && *(stacks[0]->content) == des_min)
		order = NO_ORDER;
	else
		order = ft_insertionsort(stacks[0], src_limit, -1, -1);	
	if (order == PA_ORDER)
		order = NO_ORDER;
	return (order);
}

static void ft_getin_position(t_list **stacks, char **order_lst)
{
	int	run;
	int	order_a;
	int	order_b;

	run = ft_lstlast(stacks[1])->run;
	if (ft_lstsize(stacks[1]) == ft_runsize(stacks[1], run))
		run = -1;
	while (ft_lstlast(stacks[1])->run == run || order_a != NO_ORDER)
	{
		order_b = RRB_ORDER;
		order_a = ft_des_position(stacks, run);
		if (ft_lstlast(stacks[1])->run != run || run == -1)
			order_b = NO_ORDER;
		if (run == -1 && order_a == NO_ORDER)
			break;
		if (order_a == order_b - 3)
		{
			order_a = order_b + 3;
			order_b = NO_ORDER;
		}
		if (ft_execute(order_b, stacks))
			ft_printf("%s\n", order_lst[order_b]);
		if (ft_execute(order_a, stacks))
			ft_printf("%s\n", order_lst[order_a]);
	}
}

void	ft_mergesort(t_list **stacks, char **order_lst, int run_a, int run_b)
{
	int	order;
	int	next;

	ft_getin_position(stacks, order_lst);
	next = *(ft_limitchr(stacks[1], run_a, 1)->content);
	if (next < *(ft_limitchr(stacks[1], run_b, 1)->content))
		next = *(ft_limitchr(stacks[1], run_b, 1)->content);
	while (ft_runsize(stacks[1], run_a) || ft_runsize(stacks[1], run_b))
	{
		order = ft_mergepair(stacks[1], stacks[0], run_a, run_b);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	}
}
