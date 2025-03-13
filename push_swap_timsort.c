/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_timsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/13 21:22:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_printruns(t_list *stack)
{
	while (stack)
	{
		ft_printf("NBR |%i|%i| RUN\n", *(stack->content), stack->run);
		stack = stack->next;
	}
}
void	ft_timsort(t_list **stacks, char **order_lst)
{
	int run_a;
	int run_b;
	
	ft_quicksort(stacks, order_lst, 9);
	ft_bubblesort(stacks, order_lst, 0, -1);
	while (stacks[1])
	{
		run_a = ft_lstlast(stacks[1])->run;
		if (ft_lstsize(stacks[1]) != ft_runsize(stacks[1], run_a))
			run_b = run_a + 1;
		else
			run_b = run_a;
		ft_mergesort(stacks, order_lst, run_a, run_b);
	}
	while (ft_checksort_lst(stacks[0], 0))
		if (ft_execute(RRA_ORDER, stacks))
			ft_printf("%s\n", order_lst[RRA_ORDER]);	
}
