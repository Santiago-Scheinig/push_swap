/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/13 16:54:10 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_merge_runs(t_list **stacks, char **order_lst, int minrun, int col)
{
	int	run_a;
	int	run_b;
	int	run_len;
	int	paralel;

	paralel = 0;
	if (!col)
		paralel = 1;
	if (!stacks[paralel])
		run_b = stacks[paralel]->run;
	run_a = stacks[col]->run;
	
	else
		while (condition)
		{
			/* code */
		}
		run_a = stacks[col]->run;
}

void	ft_inverse_run(t_list **stacks, char **order_lst, int col)
{
	int	paralel;
	int order_push;
	int order_reverse;

	paralel = 0;
	order_push = PA_ORDER;
	order_reverse = RA_ORDER;
	if (!col)
	{
		paralel = 1;
		order_push = PB_ORDER;
		order_reverse = RA_ORDER;
	}
	while (stacks[col]->run == -1)
	{
		if (ft_execute(order_push, stacks))
			ft_printf("%s\n", order_lst[order_push]);
		if (ft_execute(order_reverse, stacks))
			ft_printf("%s\n", order_lst[order_reverse]);
	}
	ft_setruns(stacks[paralel], 0, 1);
}

int	ft_mergesort(t_list **stacks, char **order_lst, int *minrun, int col)
{
	int	run_a;
	int	run_b;
	int	run_a_size;
	int	run_b_size;
	
	run_a = stacks[col]->run;
	run_b = ft_lstlast(stacks[col])->run;
	if (run_a == -1)
		if (stacks[col]->next->run == -1)
			ft_inverse_run(stacks, order_lst, col);
	ft_mergeruns(stacks, order_lst, minrun, col);
}