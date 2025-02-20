/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/20 21:49:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_pushrun(t_list **stacks, char **order_lst, int run, int col_src)
{
	int	order;

	order = PB_ORDER;
	if (col_src)
		order = PA_ORDER;
	while (stacks[col_src]->run == run)
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
}

static void	ft_stack_sort(t_list **stacks, char **order_lst, int dir)
{
	t_list *limit_pos;
	int	limit;
	int	order;

	limit_pos = stacks[0];
	limit = *(ft_limitchr(stacks[0], -1, dir)->content);
	if ((dir >= 0 && *(stacks[1]->content) > limit) 
	|| (dir < 0 && *(stacks[1]->content) < limit))
	{
		limit_pos = ft_lstlast(stacks[0]);
		limit = *(ft_limitchr(stacks[0], -1, dir)->content);
		dir *= -1;
	}
	else
		return ;
	if (*(limit_pos->content) != limit)
		order = ft_get_distance(stacks[0], limit, dir);
	if (order <= ft_lstsize(stacks[0]) / 2)
		order = RA_ORDER;
	else
		order = RRA_ORDER;
	while (*(stacks[0]->content) != limit)
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
}

static void	ft_mergeruns(t_list **stacks, char **orders, int dir)
{
	int	loop;
	int	src_run;
	int	order;

	loop = 0;
	src_run = stacks[1]->run;
	while (stacks[1] && loop < 1)
	{
		if (stacks[1]->run != src_run)
		{
			src_run = stacks[1]->run;
			dir *= -1;
			ft_stack_sort(stacks, orders, dir);
			//ft_print_stack(stacks);
			loop++;
		}
		if ((dir < 0 && *(stacks[1]->content) < *(stacks[0]->content))
		|| (dir >= 0 && *(stacks[1]->content) > *(ft_lstlast(stacks[0])->content)))
			order = PA_ORDER;
		else if (dir < 0)
			order = RA_ORDER;
		else if (dir >= 0)
			order = RRA_ORDER;
		if (ft_execute(order, stacks))
			ft_printf("%s\n", orders[order]);
		ft_print_stack(stacks);
	}
}

void	ft_mergesort(t_list **stacks, char **order_lst)
{
	ft_pushrun(stacks, order_lst, stacks[1]->run, 1);
	ft_print_stack(stacks);
	ft_mergeruns(stacks, order_lst, -1);
}