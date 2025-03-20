/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/20 15:40:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Returns the most eficient order to sort a numeric T_LIST *, size 3 <=,	*/
/*	from maximum to minimum, with a O(n) order solution.					*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- For T_LIST * of size > 3, will return the most efficient order to 	*/
/*	  sort the first two numbers of the list, if any.						*/
static int	ft_maxmin_orders(t_list *stack)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;
	int	size;

	if (!stack || !stack->next)
		return (NO_ORDER);
	size = ft_lstsize(stack);
	nbr_i = *(stack->content);
	nbr_j = *(stack->next->content);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i < nbr_j && size <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i < nbr_l)
				return (RA_ORDER);
	if (nbr_i > nbr_j && size <= 3)
		if (nbr_j < nbr_l)
			return (RRA_ORDER);
	if (nbr_i < nbr_j)
		return (SA_ORDER);
	return (NO_ORDER);
}

/*	Returns the most eficient order to sort a numeric T_LIST *, size 3 <=,	*/
/*	from minimum to maximum, with a O(n) order solution.					*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- For T_LIST * of size > 3, will return the most efficient order to 	*/
/*	  sort the first two numbers of the list, if any.						*/
static int	ft_minmax_orders(t_list *stack)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;
	int	size;

	if (!stack || !stack->next)
		return (NO_ORDER);
	size = ft_lstsize(stack);
	nbr_i = *(stack->content);
	nbr_j = *(stack->next->content);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i > nbr_j && size <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (RA_ORDER);
	if (nbr_i < nbr_j && size <= 3)
		if (nbr_j > nbr_l)
			return (RRA_ORDER);
	if (nbr_i > nbr_j)
		return (SA_ORDER);
	return (NO_ORDER);
}

static void	ft_solve(t_list **stacks, char **order_lst)
{
	t_pair order;
	
	order.a = ft_minmax_orders(stacks[0]);
	order.b = ft_translate(ft_maxmin_orders(stacks[1]));
	if (order.a == order.b - 3)
	{
		order.b += 3;
		order.a = NO_ORDER;
	}
	if (ft_execute(order.a, stacks))
		ft_printf("%s\n", order_lst[order.a]);
	if (ft_execute(order.b, stacks))
		ft_printf("%s\n", order_lst[order.b]);
}
/*	Executes instructions to sort an individual stack of a numeric 			*/ 
/*	T_LIST ** with an order efficiency of: O(n).							*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- For T_LIST * of size > 6, it will only sort the first two				*/
/*	  numbers of both stacks.												*/
void	ft_bubblesort(t_list **stacks, char **order_lst)
{
	t_pair	run;
	int		lstsize;

	lstsize = ft_lstsize(stacks[0]);
	if (lstsize <= 6)
	{
		while (lstsize-- > 3)
		{
			stacks[0]->run = 0;
			if (ft_execute(PB_ORDER, stacks))
				ft_printf("%s\n", order_lst[PB_ORDER]);
		}
		while (ft_checksort_lst(stacks[0], -1) 
			|| ft_checksort_lst(stacks[1], 1))
			ft_solve(stacks, order_lst);
		run.a = 0;
		run.b = 0;
		if (stacks[1])
			ft_mergesort(stacks, order_lst, &run);
		while (ft_checksort_lst(stacks[0], -1))
			if (ft_execute(RRA_ORDER, stacks))
				ft_printf("%s\n", order_lst[RRA_ORDER]);
	}
	else
		ft_solve(stacks, order_lst);
}
