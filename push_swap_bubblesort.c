/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/06 17:53:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

/* Sorts a numeric T_LIST * with size <= 3 with a O(n) order solution.		*/
/* - Use negative orientation to sort from min to max.						*/
/* - Use positive orientation to sort from max to min.						*/
/* - Undefined behavior for T_LIST * larger than specified.					*/
void	ft_bubblesort(t_list **stacks, char **order_arr, int orientation)
{
	int	order;

	order = NO_ORDER;
	while (ft_check_sort(stacks[0], orientation))
	{
		order = ft_orders(stacks[0], orientation);
		ft_execute(order, stacks);
		ft_printf("%s\n", order_arr[order]);
	}
}