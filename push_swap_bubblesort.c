/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/25 17:07:43 by sscheini         ###   ########.fr       */
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
	if (nbr_l != nbr_j && size <= 3)
			if (nbr_i < nbr_l)
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
	if (nbr_l != nbr_j && size <= 3)
			if (nbr_i > nbr_l)
				return (RRA_ORDER);
	if (nbr_i > nbr_j)
		return (SA_ORDER);
	return (NO_ORDER);
}

/*	Executes up to three instructions to sort an individual stack of a		*/ 
/*	numeric T_LIST ** with a O(n) order solution.							*/
/*  - Use column to indicate which stack to sort:							*/
/*	|| STACK A == 0															*/
/*	|| STACK B == 1															*/
/*	- Use direction < 0, to indicate a minimum to maximum sort. 			*/
/*	- Use direction >= 0, to indicate a maximum to minimum sort. 			*/
/*																			*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- For T_LIST * of size > 3, it will only sort the first two				*/
/*	  numbers of the indicated stack.										*/
void	ft_bubblesort(t_list **stacks, char **order_lst, int col, int dir)
{
	int	order;
	int	count;

	count = -1;
	while (++count < 3)
	{
		order = NO_ORDER;
		if (dir < 0)
			order = ft_minmax_orders(stacks[col]);
		if (dir >= 0)
			order = ft_maxmin_orders(stacks[col]);
		if (col)
			order = ft_translate(order);
		if (ft_execute(order, stacks))
			ft_printf("%s\n", order_lst[order]);
	}
}