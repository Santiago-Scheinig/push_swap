/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/20 17:56:22 by sscheini         ###   ########.fr       */
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
	int	size;

	if (!stack || !stack->next)
		return (NO_ORDER);
	size = ft_lstsize(stack);
	nbr_i = *(stack->content);
	nbr_j = *(stack->next->content);
	//ft_printf("NBR I |%i| - NBR J |%i|\n", nbr_i, nbr_j);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i < nbr_j && size <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i < nbr_l)
				return (RA_ORDER);
	if (nbr_l != nbr_j && size <= 3)
			if (nbr_i < nbr_l)
				return (RRA_ORDER);
	if (nbr_i < nbr_j)
		return (SA_ORDER);
	return (NO_ORDER);
}

/* Sorts a stack of numeric T_list * from minimum to maximum, with a 		*/
/* O(n) order solution.														*/
static int	ft_orders(t_list *stack)
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
	//ft_printf("NBR I |%i| - NBR J |%i|\n", nbr_i, nbr_j);
	nbr_l = *(ft_lstlast(stack)->content);
	if (nbr_i > nbr_j && size <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (RA_ORDER);
	if (nbr_l != nbr_j && size <= 3)
			if (nbr_i > nbr_l)
				return (RRA_ORDER);
	if (nbr_i > nbr_j)
		return (SA_ORDER);
	return (NO_ORDER);
}

/*	Sorts an individual stack of a numeric T_LIST ** with a					*/
/*	O(n) order solution.													*/
/*  - Use column to indicate which stack to sort. STACK A | 0 is sorted 	*/
/*	  minimum to maximum, STACK B | 1 is sorted maximum to minimum.			*/
/*	- Use loop to indicate the amount of extra numbers to push from the		*/
/*	  opposite stack, and sort in the indicated one.						*/
/*	- Notice that, for stacks of size > 3, it will only sort the first two	*/
/*	  numbers of the indicated stack.										*/
void	ft_bubblesort(t_list **stacks, char **order_lst, int col, int dir)
{
	int	order;
	int	count;

	count = -1;
	while (++count < 3)
	{
		order = NO_ORDER;
		//ft_printf("COUNT |%i|\n", count);
		if (dir <= 0)
			order = ft_orders(stacks[col]);
		if (dir > 0)
			order = ft_inverse_orders(stacks[col]);
		if (col)
			order += 3;
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	}
}
