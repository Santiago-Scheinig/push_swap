/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_timsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/25 22:43:52 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_printruns(t_list	*stack)
{
	while (stack)
	{
		ft_printf("NBR |%i| - RUN |%i|\n", *(stack->content), stack->run);
		stack = stack->next;
	}		
}

int	ft_get_minrun(int	stack_len)
{
	int	min_run;

	min_run = 32;
	while ((stack_len / min_run) % 2 != 0 || (stack_len / min_run) / 2 != 0)
		min_run--;
	return (min_run);
}

int	ft_sort_run(t_list *stack, int run, int dir, int col)
{
	int	count;
	int	limit;
	int	order;

	count = 0;
	order = RA_ORDER;
	limit = *(ft_limitchr(stack, run, dir)->content);
	stack = ft_runchr(stack, run, &count);
	while (stack && stack->run == run)
	{
		if (*(stack->content) == limit)
			break ;
		count++;
		stack = stack->next;
	}
	if (!count)
		return (NO_ORDER);
	if (count < ft_lstsize(stack) / 2)
		order = RRA_ORDER;
	if (col)
		order += 3;
	return (order);
}

void	ft_run_maker(t_list **stacks, char **order_lst, int run, int dir)
{
	int	order;
	int	run_size;

	run_size = ft_runsize(stacks[1], run);
	while (run_size < 8)
	{
		//ft_print_stack(stacks);
		if (!stacks[0])
			break ;
		order = ft_insertionsort(stacks[1], *(stacks[0]->content), run, dir);
		if (dir < 0)
			order = ft_translate(order);
		if (ft_execute(order, stacks))
		{
			ft_printf("%s\n", order_lst[order]);
			if (order == PB_ORDER)
			{
				stacks[1]->run = run;
				run_size++;
			}
		}
	}
}

void	ft_minrun_split(t_list **stacks, char **order_lst, int run)
{
	int order;
	int	limit;
	int	count;
	int	dir;

	dir = 1;
	while (ft_lstsize(stacks[0]) >= 8)
	{
		count = -1;
		while (++count < 2)
			if (ft_execute(PB_ORDER, stacks))
				ft_printf("%s\n", order_lst[PB_ORDER]);
		stacks[1]->run = run;
		stacks[1]->next->run = run;
		ft_bubblesort(stacks, order_lst, 1, dir);
		ft_run_maker(stacks, order_lst, run, dir);
		limit = *(ft_limitchr(stacks[1], run, dir)->content);
		order = ft_sort_run(stacks[1], run, dir, 1);
		while (*(stacks[1]->content) != limit)
			if (ft_execute(order, stacks))
				ft_printf("%s\n", order_lst[order]);
		dir *= -1;
		run++;
	}
}


void	ft_timsort(t_list **stacks, char **order_lst)
{
	int	limit;
	int	order;
	int	run;

	ft_quicksort(stacks, order_lst, 25);
	//ft_print_stack(stacks);
	//ft_printruns(stacks[1]);
	return ;
	ft_minrun_split(stacks, order_lst, 0);
	//ft_print_stack(stacks);
	run = stacks[1]->run;
	while (stacks[0])
	{
		order = ft_insertionsort(stacks[1], *(stacks[0]->content), run, -1);
		order = ft_translate(order);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
		if (order == PA_ORDER || order == PB_ORDER)
			stacks[1]->run = run;
		//ft_print_stack(stacks);
	}
	limit = *(ft_limitchr(stacks[1], run, -1)->content);
	order = ft_sort_run(stacks[1], run, -1, 1);
	while (*(stacks[1]->content) != limit)
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	//ft_print_stack(stacks);
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 0);
/*  	ft_printf("\nSTACK A\n");
	ft_printruns(stacks[0]);
	ft_printf("\nSTACK B\n");
	ft_printruns(stacks[1]); */
	return ;
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 0);
}
