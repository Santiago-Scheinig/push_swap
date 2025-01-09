/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_algorithms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/09 23:08:40 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Shell sort for 5+: Pass 5, Quick sort them. Repeat the process til there's */
/* no numbers left in a.*/
/* Quick sort for 4 or 5 nbrs.	  */
/* Bubble sort for 3 nbrs or less.*/

/*									   {P, S, R, RR}						*/
/* Every order for stack_a is saved on {0, 2, 4, 6 } (even numbers).		*/
/* Every order for stack_b is saved on {1, 3, 5, 7 } (odd numbers).			*/
/* The formula being:														*/
/* Instruction index = (column % 2) + (2 * pair).								*/
/* ____________________________________________________________				*/
/* | column | P (pair 0)| S (pair 2)| R (pair 4)| RR (pair 6) |				*/
/* |--------|-----------|-----------|-----------|-------------|				*/
/* | A = 0  | A % 2 = 0 | A % 2 = 2 | A % 2 = 4 |  A % 2 = 6  |				*/
/* | B = 1  | B % 2 = 1 | B % 2 = 3 | B % 2 = 4 |  B % 2 = 7  |				*/
/* |________|___________|___________|___________|_____________|				*/
/*																			*/
int ft_bubblesort(t_list *stack, int column)
{
	int	*nbr_i;
	int	*nbr_j;

	nbr_i = stack->content;
	nbr_j = stack->next->content;
	if ((*nbr_i) > (*nbr_j))
	{
		if (stack->next->next)
		{
			nbr_j = stack->next->next->content;
			if ((*nbr_i) > (*nbr_j))
				return ((column % 2) + 4);
		}
		return ((column % 2) + 2);
	}
	nbr_j = stack->next->next->content;
	if ((*nbr_i) > (*nbr_j))
		return ((column % 2) + 6);
	return ((column % 2) + 2);
}
