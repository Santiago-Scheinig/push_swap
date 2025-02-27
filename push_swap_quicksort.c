/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/27 17:49:24 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_pvtrun(t_list *stack, int pivot)
{
	while (stack)
	{
		if (*(stack->content) <= pivot)
			stack->run = -1;
		else if (*(stack->content) > pivot)
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

/* static void	ft_endrun(t_list **stacks, char **order_lst, int run, int col) //runs Max to Min
{
	t_list	*limit_pos;
	int		limit;
	int		exe_b;
	int		exe_a;

	exe_b = ft_runsort(stacks[col], run, 1, 1);
	limit = *(ft_limitchr(stacks[col], run, 1)->content);
	limit_pos = stacks[1];
 	while (*(limit_pos->content) != limit)
	{
		ft_nextnbr(stacks[1], &exe_a, run);
		if (exe_a == exe_b + 3)
			exe_b += 3;
		if (ft_execute(exe_b, stacks))
			ft_printf("%s\n", order_lst[exe_b]);
		limit_pos = stacks[1];
	}
} */

static void	ft_endrun(t_list **stacks, char **order_lst, int run, int col)
{
	t_list	*limit_pos;
	int		limit;
	int		exe_b;
	int		exe_a;

	exe_b = ft_runsort(stacks[col], run, 1, 1);
	limit = *(ft_limitchr(stacks[col], run, 1)->content);
	limit_pos = stacks[1];
	if ((run % 2) != 0)
	{
		if (exe_b == NO_ORDER)
			exe_b = RB_ORDER;
		limit_pos = ft_lstlast(stacks[1]);
	}
	while (*(limit_pos->content) != limit)
	{
		ft_nextnbr(stacks[1], &exe_a, run);
		if (exe_a == exe_b + 3)
			exe_b += 3;
		if (ft_execute(exe_b, stacks))
			ft_printf("%s\n", order_lst[exe_b]);
		limit_pos = stacks[1];
		if ((run % 2) != 0)
			limit_pos = ft_lstlast(stacks[1]);
	}
}

/*	Returns the most eficient pair of orders needed to sort both stacks.	*/
/*	- The orders are recover from executing Bubblesort and Insertionsort,	*/
/*	  in combination with other logical factors.							*/
/*	- Runlen == 0 means no subdivision.										*/
static int	ft_get_orders(t_list **stacks, int *exe_a, int *exe_b, int rlen)
{
	t_list	*next_nbr;
 	int		dir;
	int		run;

 	run = 0;
 	dir = 1;
	while (rlen && ft_runsize(stacks[1], run) >= rlen)
		run++;
 	if ((run % 2) != 0)
		dir *= -1;
	next_nbr = ft_nextnbr(stacks[0], exe_a, -1);
	*(exe_b) = ft_insertionsort(stacks[1], *(next_nbr->content), run, dir);
	*(exe_b) = ft_translate(*(exe_b));
	if (rlen && stacks[1] && ft_runsize(stacks[1], run) >= rlen)
	{
		*(exe_b) = PB_ORDER;
		run++;
	}
	if (*(exe_a) == NO_ORDER && *(exe_b) == PB_ORDER)
		if (*(stacks[0]->content) == *(next_nbr->content))
			stacks[0]->run = run;
	if (*(exe_a) != NO_ORDER && *(exe_b) == PB_ORDER)
		*(exe_b) = NO_ORDER;
	return (run);
}

/*	Sorts a stack of a numeric T_LIST ** with an order solution eficiency	*/
/*	from: O(n^2) to O(n log (n)).											*/
/*	- To sort the stack it will split it with a middle pivot and push every */
/*	  minimum number found to the second stack, using Insertionsort to		*/
/*	  secure the correct sorting. It will repeat this process everytime	the	*/
/*	  pivot is pushed, becoming more efficient after each repetition.		*/
/*  - Notice that the first order solution eficiency increases exponencialy	*/
/*	  with the amount of values.											*/
void	ft_quicksort(t_list **stacks, char **order_lst, int rlen)
{
	int	run;
	int	exe_a;
	int	exe_b;

	run = 0;
	ft_pvtrun(stacks[0], ft_pvtchr(stacks[0], stacks[0]));
	while (ft_lstsize(stacks[0]) > 3 && ft_checksort_lst(stacks[0], 0))
	{
		if (rlen && !ft_runsize(stacks[0], -1) && ft_lstsize(stacks[0]) > rlen)
			ft_pvtrun(stacks[0], ft_pvtchr(stacks[0], stacks[0]));
		else if (!ft_runsize(stacks[0], -1))
			ft_pvtrun(stacks[0], *(ft_limitchr(stacks[0], -1, 1)->content));
		run = ft_get_orders(stacks, &exe_a, &exe_b, rlen);
		if (exe_a == exe_b - 3)
			exe_b += 3;
		if (exe_b >= 8)
			exe_a = NO_ORDER;
		if (ft_execute(exe_a, stacks))
			ft_printf("%s\n", order_lst[exe_a]);
		if (ft_execute(exe_b, stacks))
			ft_printf("%s\n", order_lst[exe_b]);
		if (rlen && stacks[1] && ft_runsize(stacks[1], run) >= rlen)
			ft_endrun(stacks, order_lst, run, 1);
	}
	ft_endrun(stacks, order_lst, run, 1);
}
