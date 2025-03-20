/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:35:26 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/20 15:27:03 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Initializes the run of every single node of a numeric T_LIST * in		*/
/*	correlation with the pivot.												*/
/*	- Numbers lesser or equal than the pivot will get run = -1.				*/
/*	- Numbers bigger than the pivot will get run = 1.						*/
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

/*	Executes the most efficient orders to sort an individual run with a		*/
/*	rollercoaster format.													*/
/*	- If the run is pair, it will sort it leaving the minimum limit on 		*/
/*	  first position.														*/
/*	- If the run is odd, it will sort it leaving the maximum limit on 		*/
/*	  first position.														*/
/*	- If only one run exists, it will sort it leaving the maximum limit on	*/
/*	  first position.														*/
static void	ft_endrun(t_list **stacks, char **order_lst, int run, int col)
{
	t_list	*limit_pos;
	int		limit;
	int		exe_b;
	int		exe_a;

	exe_b = ft_translate(ft_runsort(stacks[col], run, 1));
	limit = *(ft_limitchr(stacks[col], run, 1)->content);
	limit_pos = stacks[1];
	if ((run % 2) != 0)
	{
		exe_b = ft_translate(ft_runsort(stacks[col], run, -1));
		limit = *(ft_limitchr(stacks[col], run, -1)->content);
	}
	while (*(limit_pos->content) != limit)
	{
		ft_nextnbr(stacks[0], &exe_a, 1);
		if (exe_a == exe_b - 3)
		{
			if (ft_execute(exe_b + 3, stacks))
				ft_printf("%s\n", order_lst[exe_b + 3]);
		}
		else if (ft_execute(exe_b, stacks))
			ft_printf("%s\n", order_lst[exe_b]);
		limit_pos = stacks[1];
	}
}

/*	Saves the most efficient pair of orders needed to sort the stacks in	*/
/*	ORDER, then return the current run being sorted.						*/
/*	- The orders are recover from executing Insertionsort in combination 	*/
/*	with other logical factors.												*/
/*	- Use negative pvt to indicate the numbers to push to be lesser or equal*/
/*	  to the pivot.															*/
/*	- Use positive pvt to indicate the numbers to push to be higher			*/
/*	  to the pivot.															*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- If rlen is defined, it will return the most eficient pair of orders	*/
/*	  needed to sort the runs instead.										*/
static int	ft_get_orders(t_list **stacks, t_pair *order, int pvt, int rlen)
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
	next_nbr = ft_nextnbr(stacks[0], &order->a, pvt);
	order->b = ft_insertionsort(stacks[1], *(next_nbr->content), run, dir);
	order->b = ft_translate(order->b);
	if (rlen && stacks[1] && ft_runsize(stacks[1], run) >= rlen && run++)
		order->b = PB_ORDER;
	if (order->a == NO_ORDER && order->b == PB_ORDER)
		if (*(stacks[0]->content) == *(next_nbr->content))
			stacks[0]->run = run;
	if (order->a != NO_ORDER && order->b == PB_ORDER)
		order->b = NO_ORDER;
	if (order->a == order->b - 3)
		order->b += 3;
	if (order->b >= SS_ORDER)
		order->a = NO_ORDER;
	return (run);
}

/*	Sorts a stack of a numeric T_LIST ** with an order solution efficiency	*/
/*	of: O(n^2) to O(n log (n)).												*/
/*	- To sort the stack it will split it with a middle pivot and push every	*/
/*	  number bigger than the pivot to the second stack, using Insertionsort	*/
/*	  to verify the correct sorting. Then, it will repeat the same process	*/
/*	  with the numbers lesser than the pivot.								*/
/*	- Use rlen != 0 to subdivide the numbers sorted with Insertionsort into */
/*	  runs of the decleared size.											*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- If rlen is define, quicksort doesn't sort the totallity of the stack, */
/*	  but the subdivided runs.												*/
/*	- Additionally, once the first round of bigger numbers is pushed to the	*/
/*	  second stack, it will find the pivot of the remaining numbers, and	*/
/*	  push the lesser numbers this time, repeating this last process until	*/
/*	  only one number is left.												*/
void	ft_quicksort(t_list **stacks, char **order_lst, int rlen)
{
	t_pair	order;
	t_pair	run;

	run.a = 1;
	run.b = 0;
	ft_pvtrun(stacks[0], ft_pvtchr(stacks[0], stacks[0]));
	while (ft_lstsize(stacks[0]) > 1)
	{
		if (rlen && !ft_runsize(stacks[0], run.a)
			&& ft_lstsize(stacks[0]) > rlen)
		{
			ft_pvtrun(stacks[0], ft_pvtchr(stacks[0], stacks[0]));
			run.a = -1;
		}
		else if (!ft_runsize(stacks[0], run.a))
			ft_pvtrun(stacks[0], *(ft_limitchr(stacks[0], -1, -1)->content));
		run.b = ft_get_orders(stacks, &order, run.a, rlen);
		if (ft_execute(order.a, stacks))
			ft_printf("%s\n", order_lst[order.a]);
		if (ft_execute(order.b, stacks))
			ft_printf("%s\n", order_lst[order.b]);
		if ((rlen && ft_runsize(stacks[1], run.b) >= rlen)
			|| ft_lstsize(stacks[0]) == 1)
			ft_endrun(stacks, order_lst, run.b, 1);
	}
}
