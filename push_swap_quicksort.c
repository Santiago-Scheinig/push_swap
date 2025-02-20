/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/20 17:29:04 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Returns the middle pivot of a numeric T_LIST * with a O(n^2) space		*/
/*	complexity.																*/
static int	ft_pvtchr(t_list *stack, t_list *start)
{
	t_list	*tmp;
	int		top;
	int		pivot;
	int		bottom;

	if (!stack || ft_lstsize(stack) <= 3)
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
		return (ft_pvtchr(stack, ft_nextnbr_chr(start, pivot, -1)));
	return (ft_pvtchr(stack, ft_nextnbr_chr(start, pivot, 1)));
}

/*	After both stacks are confirmed to be sorted, if any values are still 	*/
/*	on the STACK_B, it will merge them back to STACK_A using Insertionsort.	*/
static void	ft_merge(t_list **stacks, char **order_arr)
{
	int	limit;
	int	order;
	
	ft_printf("MERGE");
	while (stacks[1])
	{
		order = ft_insertionsort(stacks[0], *(stacks[1]->content), -1, -1);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_arr[order]);
	}
	limit = *(ft_limitchr(stacks[0], -1, -1)->content);
	while (ft_checksort_lst(stacks[0], -1))
	{
		order = ft_get_distance(stacks[0], limit, 1);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_arr[order]);	
	}
}

/*	Returns the most eficient pair of orders needed to sort both stacks.	*/
/*	- The orders are recover from executing Bubblesort and Insertionsort,	*/
/*	  in combination with other logical factors.							*/
static int	ft_orders(t_list **stacks, int *order_b, int *pivot)
{
	t_list	*tmp;
	int		order_a;
	int		next_nbr;

	order_a = NO_ORDER;
	tmp = ft_nextnbr_chr(stacks[0], *(pivot), -1);
	if (!tmp)
		tmp = stacks[0];
	if (ft_checksort_lst(stacks[0], -1))
	{
		next_nbr = *(tmp->content);
		ft_printf("NEXT NBR QUICKSORT |%i|\n", next_nbr);
		if ((*(stacks[0]->content)) < (*pivot) || *(stacks[0]->content) == next_nbr)
			order_a = PB_ORDER;
		else
			order_a = RA_ORDER;
		if ((*(stacks[0]->content)) == (*pivot))
			(*pivot) = ft_pvtchr(stacks[0], stacks[0]);
		*(order_b) = ft_insertionsort(stacks[1], next_nbr, -1, 1);
	}
	if (*(order_b) > NO_ORDER && order_a == PB_ORDER)
		order_a = NO_ORDER;
	if (order_a == PB_ORDER && *(order_b) == PB_ORDER)
		*(order_b) = NO_ORDER;
	return (order_a);
}

/*	Sorts a stack of a numeric T_LIST ** with an order solution eficiency	*/
/*	from: O(n^2) to O(n log (n)).											*/
/*	- To sort the stack it will split it with a middle pivot and push every */
/*	  minimum number found to the second stack, using Insertionsort to		*/
/*	  secure the correct sorting. It will repeat this process everytime	the	*/
/*	  pivot is pushed, becoming more efficient after each repetition.		*/
/*  - Notice that the first order solution eficiency increases exponencialy	*/
/*	  with the amount of values.											*/
void	ft_quicksort(t_list **stacks, char **order_arr)
{
	int	pivot;
	int	order_a;
	int	order_b;
	int	loop;

	loop = 0;
	pivot = ft_pvtchr(stacks[0], stacks[0]);
	while (((ft_checksort_lst(stacks[0], -1)) || ft_checksort_lst(stacks[1], 1)) && ++loop < 10)
	{
		ft_print_stack(stacks);
		order_b = NO_ORDER;
		order_a = ft_orders(stacks, &order_b, &pivot);
		if (order_a == order_b - 3)
		{
			if (ft_execute(order_b + 3, stacks))
				ft_printf("%s\n", order_arr[order_b + 3]);
			continue ;
		}
		if (ft_execute(order_a, stacks))
			ft_printf("%s\n", order_arr[order_a]);
		if (ft_execute(order_b, stacks))
			ft_printf("%s\n", order_arr[order_b]);
		if (ft_lstsize(stacks[0]) <= 3)
			ft_bubblesort(stacks, order_arr, 0, 0);
	}
	ft_merge(stacks, order_arr);
}
