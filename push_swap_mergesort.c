/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_mergesort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:33:40 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/17 16:24:32 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Returns the most efficient order needed to merge both run_a and run_b	*/
/*	into the STACK A.														*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- It only merges and sorts the runs into the STACK A from minimum to	*/
/*	  maximum.																*/
static int	ft_mergepair(t_list *src, t_list *des, int run_a, int run_b)
{
	t_list	*src_last;
	t_list	*des_last;
	int		order;

	order = NO_ORDER;
	src_last = ft_lstlast(src);
	des_last = ft_lstlast(des);
	if ((src_last->run == run_a || src_last->run == run_b) && run_a != run_b)
		if ((src->run != run_a && src->run != run_b)
			|| (*(src->content) < *(src_last->content)))
			order = RRB_ORDER;
	if (order == RRB_ORDER && *(des_last->content) > *(src_last->content))
		if (src_last->run == run_a || src_last->run == run_b)
			if (*(des->content) > *(des_last->content))
				order = RRR_ORDER;
	if (order == NO_ORDER)
	{
		order = PA_ORDER;
		if (*(des_last->content) > *(src->content)
			&& *(des->content) != *(ft_limitchr(des, -1, -1)->content))
			order = RRA_ORDER;
	}
	return (order);
}

/*	Returns the most efficient order needed to positionate the STACK A to	*/
/*	be ready to merge both runs sent as argument.							*/
/*	- If the STACK A it's already on it's correct position, 				*/
/*	  returns NO_ORDER.														*/
static int	ft_des_position(t_list **stacks, t_pair *run)
{
	int		order;
	int		des_max;
	int		des_min;
	int		src_limit;

	src_limit = *(ft_limitchr(stacks[1], run->a, 1)->content);
	if (run->a >= 0)
		if (src_limit < *(ft_limitchr(stacks[1], run->b, 1)->content))
			src_limit = *(ft_limitchr(stacks[1], run->b, 1)->content);
	des_min = *(ft_limitchr(stacks[0], -1, -1)->content);
	des_max = *(ft_limitchr(stacks[0], -1, 1)->content);
	if (src_limit > des_max && *(stacks[0]->content) == des_min)
		order = NO_ORDER;
	else
		order = ft_insertionsort(stacks[0], src_limit, -1, -1);
	if (order == PA_ORDER)
		order = NO_ORDER;
	return (order);
}

/*	Executes the orders needed to leave both stacks in position and ready	*/
/*	to merge the runs sent as argument.										*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- This function becomes more efficient if the first run to merge it's 	*/
/*	  the first of the stack.												*/
static void	ft_getin_invpos(t_list **stacks, char **order_lst, t_pair *run)
{
	t_pair	order;

	if (ft_lstsize(stacks[1]) == ft_runsize(stacks[1], run->a))
		run->a = -1;
	while (stacks[1]->run == run->a || order.a != NO_ORDER)
	{
		order.b = RB_ORDER;
		order.a = ft_des_position(stacks, run);
		if (stacks[1]->run != run->a || run->a == -1 || run->a == run->b)
			order.b = NO_ORDER;
		if ((run->a == -1 || run->a == run->b) && order.a == NO_ORDER)
			break ;
		if (order.a == order.b - 3)
		{
			order.a = order.b + 3;
			order.b = NO_ORDER;
		}
		if (ft_execute(order.b, stacks))
			ft_printf("%s\n", order_lst[order.b]);
		if (ft_execute(order.a, stacks))
			ft_printf("%s\n", order_lst[order.a]);
	}
}

/*	Executes the orders needed to leave both stacks in position and ready	*/
/*	to merge the runs sent as argument.										*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- This function becomes more efficient if the first run to merge it's 	*/
/*	  the last of the stack.												*/
static void	ft_getin_pos(t_list **stacks, char **order_lst, t_pair *run)
{
	t_pair	order;

	if (ft_lstsize(stacks[1]) == ft_runsize(stacks[1], run->a))
		run->a = -1;
	while (ft_lstlast(stacks[1])->run == run->a || order.a != NO_ORDER)
	{
		order.b = RRB_ORDER;
		order.a = ft_des_position(stacks, run);
		if (ft_lstlast(stacks[1])->run != run->a || run->a == -1)
			order.b = NO_ORDER;
		if ((run->a == -1 || run->a == run->b) && order.a == NO_ORDER)
			break ;
		if (order.a == order.b - 3)
		{
			order.a = order.b + 3;
			order.b = NO_ORDER;
		}
		if (ft_execute(order.b, stacks))
			ft_printf("%s\n", order_lst[order.b]);
		if (ft_execute(order.a, stacks))
			ft_printf("%s\n", order_lst[order.a]);
	}
}

/*	Merges and sorts a numeric T_LIST ** using the runs sent as argument 	*/
/*	with an order efficiency of: O(n log(n)).								*/
/*	- Use run.a to declare the first run to merge. This should be the run	*/
/*	  at the beggining or end of the stack.									*/
/*	- Use run.b to declare the second run to merge. This should be the run	*/
/*	  next the first run (the following or previous run respectibly).		*/
/*	- Use run.a == run.b to merge a single run.								*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- Mergesort can only sort numeric T_LIST ** with rollercoaster format.	*/
void	ft_mergesort(t_list **stacks, char **order_lst, t_pair *run)
{
	int	order;
	int	next;

	if (stacks[1]->run == run->a)
		ft_getin_invpos(stacks, order_lst, run);
	else
		ft_getin_pos(stacks, order_lst, run);
	if (run->a == run->b)
	{
		while (stacks[1]->run == run->a)
			if (ft_execute(PA_ORDER, stacks))
				ft_printf("%s\n", order_lst[PA_ORDER]);
		return ;
	}
	next = *(ft_limitchr(stacks[1], run->a, 1)->content);
	if (next < *(ft_limitchr(stacks[1], run->b, 1)->content))
		next = *(ft_limitchr(stacks[1], run->b, 1)->content);
	while (ft_runsize(stacks[1], run->a) || ft_runsize(stacks[1], run->b))
	{
		order = ft_mergepair(stacks[1], stacks[0], run->a, run->b);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	}
}
