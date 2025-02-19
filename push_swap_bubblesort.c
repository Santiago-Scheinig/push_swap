/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/19 15:08:49 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sorts a stack of numeric T_list * from maximum to maximum, with a 		*/
/* O(n) order solution.														*/
static int	ft_inverse_orders(t_list *stack)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;

	nbr_i = *(stack->content);
	nbr_j = *(stack->next->content);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i < nbr_j)
	{
		if (nbr_l != nbr_j)
			if (nbr_i < nbr_l)
				return (RB_ORDER);
	}
	else if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (RRB_ORDER);
	return (SB_ORDER);
}

/* Sorts a stack of numeric T_list * from minimum to maximum, with a 		*/
/* O(n) order solution.														*/
static int	ft_orders(t_list *stack, int orientation)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;

	if (orientation >= 0)
		return (ft_inverse_orders(stack));
	nbr_i = *(stack->content);
	nbr_j = *(stack->next->content);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i > nbr_j)
	{
		if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (RA_ORDER);
	}
	else if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (RRA_ORDER);
	return (SA_ORDER);
}

/*	Sorts an individual stack of a numeric T_LIST ** with a					*/
/*	O(n) order solution.													*/
/*  - Use column to define the stack to be sorted.							*/
/*	- Use negative direction to sort from minimum to maximum.				*/
/*	- Use positive direction to sort from maximum to minimum.				*/
/*	- If the T_LIST * size <= 3 it will execute all orders needed to sort	*/
/*	  the stack. Finally returning NO_ORDER.								*/
/*	- If the T_LIST * size >= 4 it will instead return an order if it's		*/
/*	  SA_ORDER or SB_ORDER. Otherwise, returns NO_ORDER. 					*/
/*	- Notice that in the last case, no orders will be executed.				*/
int	ft_bubblesort(t_list **stacks, char **order_lst, int dir, int col)
{
	int	order;

	order = NO_ORDER;
	while (ft_checksort_lst(stacks[col], dir))
	{
		order = ft_orders(stacks[col], dir);
		if (ft_lstsize(stacks[col]) > 3)
		{
			if (order == SA_ORDER || order == SB_ORDER)
				return (order);
			break ;
		}
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	}
	return (NO_ORDER);
}