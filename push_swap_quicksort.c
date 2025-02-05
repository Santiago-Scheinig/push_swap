/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/05 21:46:16 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Returns the middle pivot of an unsorted T_LIST *, of integers content,	*/
/* with a complexity of O(n).												*/
static int	ft_pvtchr(t_list *stack, t_list *start)
{
	t_list	*tmp;
	int		top;
	int		pivot;
	int		bottom;

	if (!stack || !*(stack->content) || ft_lstsize(stack) <= 3)
		return (0);
	top = 0;
	pivot = *(start->content);
	bottom = 0;
	tmp = stack;
	while (tmp)
	{
		if (pivot < *(tmp->content))
			top++;
		else if (pivot > *(tmp->content))
			bottom++;
		tmp = tmp->next;
	}
	if (top == bottom || top - 1 == bottom)
		return (pivot);
	else if (bottom > top)
		return (ft_pvtchr(stack, ft_lstnext_nbr(start, pivot, -1)));
	return (ft_pvtchr(stack, ft_lstnext_nbr(start, pivot, 1)));
}

//to solve, still issue with pivot.
static void	ft_merge(t_list **stacks, char **lst_instructions)
{
	int	order;
	int	loop;

	loop = 0;
	//ft_print_stack(stacks);
	return ;
	while (stacks[1] && loop++ < 20)
	{
		if ((*(stacks[0]->content)) > (*(stacks[1]->content)) && !ft_check_sort(stacks[0], -1)) 
			order = 0;
		else
			order = ft_insertionsort(stacks, *(stacks[0]->content), 1);
		if (order < 0)
			order = 0;
		if (ft_execute(order, stacks))
			ft_printf("%s\n", lst_instructions[order]);
	}
	while (ft_check_sort(stacks[0], -1) && loop++ < 22)
	{
		//ft_print_stack(stacks);
		if (ft_execute(RRA_ORDER, stacks))
			ft_printf("%s\n", lst_instructions[RRA_ORDER]);
	}
}

static int	ft_orders(t_list **stacks, int *order_b, int *pivot)
{
	int	order_a;

	order_a = NO_ORDER;
	if (ft_check_sort(stacks[0], -1))
	{
		if ((*(stacks[0]->content)) == (*pivot))
		{
			(*pivot) = ft_pvtchr(stacks[0], stacks[0]);	
			order_a = RA_ORDER;
		}
		if ((*(stacks[0]->content)) < (*pivot))
			order_a = PB_ORDER;
	}
	*(order_b) = ft_insertionsort(stacks, *(pivot), 1);
	if (*(order_b) > NO_ORDER && order_a == PB_ORDER)
		order_a = NO_ORDER;
	if (*(order_b) == NO_ORDER && ft_check_sort(stacks[1], 1))
		*(order_b) = ft_islimit(stacks[1], ft_getmin_nbr(stacks[1]), 1);
	return (order_a);
}

void	ft_quicksort(t_list **stacks, char **order_arr)
{
	int	pivot;
	int	order_a;
	int	order_b;
	int	loop;

	loop = 0;
	pivot = ft_pvtchr(stacks[0], stacks[0]);
	while (((ft_check_sort(stacks[0], -1)) || ft_check_sort(stacks[1], 1)) && ++loop < 30)
	{
		order_a = ft_orders(stacks, &order_b, &pivot);
		if (order_a == order_b - 3)
		{
			if (ft_execute(order_b + 3, stacks))
				ft_printf("%s\n", order_arr[order_b + 3]);
			continue ;
		}
		if (order_a != -1)
			if (ft_execute(order_a, stacks))
				ft_printf("%s\n", order_arr[order_a]);
		if (order_b != -1)
			if (ft_execute(order_b, stacks))
				ft_printf("%s\n", order_arr[order_b]);
	}
	ft_merge(stacks, order_arr);
}
