/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_timsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/27 19:53:40 by sscheini         ###   ########.fr       */
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

void	ft_timsort(t_list **stacks, char **order_lst)
{

	ft_quicksort(stacks, order_lst, 64);
	ft_bubblesort(stacks, order_lst, 0, -1);
	ft_mergesort(stacks, order_lst, 64);
	//ft_print_stack(stacks);
	//ft_printruns(stacks[1]);
	return ;
/* 	ft_minrun_split(stacks, order_lst, 0);
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
	order = ft_runsort(stacks[1], run, -1, 1);
	while (*(stacks[1]->content) != limit)
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	//ft_print_stack(stacks);
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 0);
  	ft_printf("\nSTACK A\n");
	ft_printruns(stacks[0]);
	ft_printf("\nSTACK B\n");
	ft_printruns(stacks[1]);
 	return ;
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 1);
	ft_mergesort(stacks, order_lst, 0); */
}
