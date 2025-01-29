/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/29 18:38:08 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sorts from maximum to minimum, with a O(n^n) deterministic solution.		*/
static	int	ft_inverse_bubblesort(t_list *stack)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;
	int	lst_len;

	nbr_i = (*(stack->content));
	nbr_j = (*(stack->next->content));
	nbr_l = (*(ft_lstlast(stack)->content));
	lst_len = ft_lstsize(stack);
	if (nbr_i < nbr_j && lst_len <= 3)
	{
		if (nbr_l != nbr_j)
			if (nbr_i < nbr_l)
				return (7);//rb
	}
	else if (lst_len <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i < nbr_l)
				return (6);//rrb
	if (nbr_i > nbr_j && ft_lstsize(stack) > 3)
		return (7);
	return (5);//sb
}

/* Sorts from minimum to maximum, with a O(n^n) deterministic solution.		*/
int ft_bubblesort(t_list *stack, int column)
{
	int	nbr_i;
	int	nbr_j;
	int	nbr_l;
	int	lst_len;

	if (column)
		return (ft_inverse_bubblesort(stack));
	nbr_i = (*(stack->content));
	nbr_j = (*(stack->next->content));
	nbr_l = (*(ft_lstlast(stack)->content));
	lst_len = ft_lstsize(stack);
	if (nbr_i > nbr_j && lst_len <= 3)
	{
		if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (4);//ra
	}
	else if (lst_len <= 3)
		if (nbr_l != nbr_j)
			if (nbr_i > nbr_l)
				return (3);//rra
	if (nbr_i < nbr_j)
		return (4);
	return (2);//sa
}