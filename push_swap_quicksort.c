/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/06 22:02:46 by sscheini         ###   ########.fr       */
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
static void	ft_merge(t_list **stacks, char **order_arr)
{
	int	order;

	while (stacks[1])
	{
		order = ft_insertionsort(stacks[0], *(stacks[1]->content), -1, 0);
		if (order == NO_ORDER && *(stacks[1]->content) < *(stacks[0]->content))
			order = PA_ORDER;
		if (order == NO_ORDER && !ft_check_sort(stacks[0], -1))
			order = PA_ORDER;
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_arr[order]);
	}
}

static int	ft_orders(t_list **stacks, int *order_b, int *pivot)
{
	t_list	*tmp;
	int		order_a;
	int		next_nbr;

	order_a = NO_ORDER;
	tmp = ft_lstnext_nbr(stacks[0], *(pivot), -1);
	if (!tmp)
		tmp = ft_lstnext_nbr(stacks[0], ft_pvtchr(stacks[0], stacks[0]), -1);
	if (ft_check_sort(stacks[0], -1))
	{
		next_nbr = *(tmp->content);
		if ((*(stacks[0]->content)) < (*pivot))
			order_a = PB_ORDER;
		else
			order_a = ft_insertionsort(stacks[0], next_nbr, 1, 0);
		if ((*(stacks[0]->content)) == (*pivot))
			(*pivot) = ft_pvtchr(stacks[0], stacks[0]);
	}
	*(order_b) = ft_insertionsort(stacks[1], next_nbr, 1, 1);
	if (*(order_b) > NO_ORDER && order_a == PB_ORDER)
		order_a = NO_ORDER;
	if (order_a < 0 && *(order_b) < 0 && ft_check_sort(stacks[1], 1))
		*(order_b) = RRB_ORDER;
	return (order_a);
}

void	ft_quicksort(t_list **stacks, char **order_arr)
{
	int	pivot;
	int	order_a;
	int	order_b;

	pivot = ft_pvtchr(stacks[0], stacks[0]);
	while (((ft_check_sort(stacks[0], -1)) || ft_check_sort(stacks[1], 1)))
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
		if (ft_lstsize(stacks[0]) <= 3)
			ft_bubblesort(stacks, order_arr, -1);
	}
	ft_merge(stacks, order_arr);
}
