/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/24 19:43:17 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* static void	ft_pushrun(t_list **stacks, char **order_lst, int run, int col_src)
{
	int	order;

	order = PB_ORDER;
	if (col_src)
		order = PA_ORDER;
	while (stacks[col_src]->run == run)
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
} */

/* static void	ft_stack_sort(t_list **stacks, char **order_lst, int dir)
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
} */

/* static void	ft_mergeruns(t_list **stacks, char **orders, int dir)
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
} */

/* static void	ft_getin_runpos(t_list **stacks, char **order_lst, int dir, int col)
{
	int order;
	int	run_a;

	order = RB_ORDER;
	if (!col)
		order = RA_ORDER;
	run_a = stacks[col]->run;
	if ((run_a % 2) == 0)
	{
		if (dir >= 0)
			run_a = ft_lstlast(stacks[col])->run + 1;
		while (stacks[col]->run != (run_a - 1))
			if (ft_execute(order, stacks))
				ft_printf("%s\n", order_lst[order]);
	}
} */

static int	ft_getorder(t_list *stack, int run_a, int run_b, int dir)
{
	t_list *last;

	last = ft_lstlast(stack);
	if ((stack->run == run_a || stack->run == run_b)
	&& (last->run == run_a || last->run == run_b))
	{
		if ((dir < 0 && *(stack->content) < *(last->content)) 
		|| (dir >= 0 && *(stack->content) > *(last->content)))
			return (PB_ORDER);
	}
	else if (stack->run == run_a || stack->run == run_b)
		if (last->run != run_a || last->run != run_b)
			return (PB_ORDER);
	if (last->run == run_a || last->run == run_b)
		return (RRA_ORDER);
	return (NO_ORDER);
}

static void	ft_mergeruns(t_list **stacks, char **order_lst, int col, int dir)
{
	t_list	*last;
	int	order;
	int	run_a;
	int	run_b;

	run_a = stacks[col]->run;
	run_b = ft_lstlast(stacks[col])->run;
	last = ft_lstlast(stacks[col]);
	while (stacks[col]->run == run_a || stacks[col]->run == run_b 
	|| last->run == run_a || last->run == run_b)
	{
		//ft_print_stack(stacks);
		order = ft_getorder(stacks[col], run_a, run_b, dir);
		if (ft_lstsize(stacks[col]) == 1)
			order = PB_ORDER;
		if (col)
			order = ft_translate(order);
		if (order == PA_ORDER || order == PB_ORDER)
			stacks[col]->run = run_a;
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
		last = ft_lstlast(stacks[col]);
		if (!last)
			break ;
	}
}

void	ft_mergesort(t_list **stacks, char **order_lst, int col_src)
{
	int	dir;
	int	limit;

	dir = -1;
	limit = *(ft_limitchr(stacks[col_src], stacks[col_src]->run, 1)->content);
	if (*(stacks[col_src]->content) == limit)
		dir = 1;
	while (stacks[col_src] && stacks[col_src]->run != ft_lstlast(stacks[col_src])->run)
	{
		ft_mergeruns(stacks, order_lst, col_src, dir);
		dir *= -1;
	}
	//ft_print_stack(stacks);
	//ft_pushrun(stacks, order_lst, stacks[1]->run, 1);
}