/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/25 22:41:20 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_set_pvtrun(t_list *stack, int pivot)
{
	while (stack)
	{
		if (*(stack->content) < pivot)
			stack->run = -1;
		else if (*(stack->content) >= pivot)
			stack->run = 1;
		stack = stack->next;
	}
}

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
	return (ft_pvtchr(stack, start->next));
}

/*	Returns the most eficient pair of orders needed to sort both stacks.	*/
/*	- The orders are recover from executing Bubblesort and Insertionsort,	*/
/*	  in combination with other logical factors.							*/
/*	- Runlen == 0 means no subdivision.										*/
static int	ft_get_orders(t_list **stacks, int *exe_a, int run, int runlen)
{
	t_list	*next_nbr;
	int		new_run;
	int		limit;
	int		exe_b;
	int		dir;

	dir = 1;
	new_run = 0;
	if (stacks[1])
		new_run = stacks[1]->run;
	next_nbr = ft_nextnbr(stacks[0], exe_a, run);
	if (runlen && stacks[1] && ft_runsize(stacks[1], stacks[1]->run) >= runlen)
	{
		new_run = stacks[1]->run + 1;
		limit = *(ft_limitchr(stacks[1], stacks[1]->run, dir)->content);
		exe_b = ft_insertionsort(stacks[1], limit, stacks[1]->run, dir * -1);
		if (*(stacks[1]->content) != limit)
			return (ft_translate(exe_b));
	}
	if (new_run % 2 != 0)
		dir *= -1;
	exe_b = ft_insertionsort(stacks[1], *(next_nbr->content), new_run, dir);
	exe_b = ft_translate(exe_b);
	if (exe_b == PB_ORDER && *(exe_a) == NO_ORDER)
		if (*(stacks[0]->content) == *(next_nbr->content))
			stacks[0]->run = new_run;
	return (exe_b);
}

/*	Sorts a stack of a numeric T_LIST ** with an order solution eficiency	*/
/*	from: O(n^2) to O(n log (n)).											*/
/*	- To sort the stack it will split it with a middle pivot and push every */
/*	  minimum number found to the second stack, using Insertionsort to		*/
/*	  secure the correct sorting. It will repeat this process everytime	the	*/
/*	  pivot is pushed, becoming more efficient after each repetition.		*/
/*  - Notice that the first order solution eficiency increases exponencialy	*/
/*	  with the amount of values.											*/
void	ft_quicksort(t_list **stacks, char **order_lst, int runlen)
{
	int	run;
	int	exe_a;
	int	exe_b;

	run = -1;
	ft_set_pvtrun(stacks[0], ft_pvtchr(stacks[0], stacks[0]));
	while (stacks[0])
	{
		if (!ft_runsize(stacks[0], run))
			run *= -1;
		exe_b = ft_get_orders(stacks, &exe_a, run, runlen);
		if (exe_a != NO_ORDER && exe_b == PB_ORDER)
			exe_b = NO_ORDER;
		if (exe_a == exe_b - 3)
		{
			if (ft_execute(exe_b + 3, stacks))
				ft_printf("%s\n", order_lst[exe_b + 3]);			
			continue ;
		}
		if (ft_execute(exe_a, stacks))
			ft_printf("%s\n", order_lst[exe_a]);
		if (ft_execute(exe_b, stacks))
			ft_printf("%s\n", order_lst[exe_b]);
	}
	ft_mergesort(stacks, order_lst, 1);
}
/* while (((ft_checksort_lst(stacks[0], -1)) || ft_checksort_lst(stacks[1], 1)) && ++loop < 10)
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
 */