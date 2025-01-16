/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bubblesort.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:17:22 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/16 20:24:25 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Insertion sort to rearange the stack_b on stack_a.							*/
/* Quick sort for stack_a, dividing it with a pivot, in smaller and				*/
/* greater, taking the smallest to stack_b.										*/

/* Radix sort for larger stacks divided in stack_b.								*/
/* Shell sort for 5+: Pass 5, Quick sort them. Repeat the process til there's	*/
/* no numbers left in a.*/
/* Quick sort for 4 or 5 nbrs.	  */
/* Bubble sort for 3 nbrs or less.*/

/*									   {P, S,       R, RR}						*/
/* Every order for stack_a is saved on {0 (pa), 2 (sa) , 4 (ra), 6 (rra)} (even numbers).		*/
/* Every order for stack_b is saved on {1 (pb), 3 (rrb), 5 (sb), 7 (rb) } (odd numbers).			*/
/* The formula being:														*/
/* Instruction index = column + (2 * pair).								*/
/* ____________________________________________________________				*/
/* | column | P (pair 0)| S (pair 2)| R (pair 4)| RR (pair 6) |				*/
/* |--------|-----------|-----------|-----------|-------------|				*/
/* | A = 0  | A + 0 = 0 | A + 2 = 2 | A + 4 = 4 |  A + 6 = 6  |				*/
/* | B = 1  | B + 0 = 1 | B + 2 = 3 | B + 4 = 5 |  B + 6 = 7  |				*/
/* |________|___________|___________|___________|_____________|				*/
/*																			*/

#include "push_swap.h"

/* 3 2 1 - 2 1 3 - 1 2 3 - 2 3 - 3 - 7 5 6 - 5 6 7 -*/
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
				return (column + 4);//ra - sb
		}
		return (column + 2);//sa - rrb
	}
	if (stack->next->next)
		nbr_j = stack->next->next->content;
	if ((*nbr_i) > (*nbr_j) && !column)
		return (column + 6);//rra - rb
	if ((*nbr_i) > (*nbr_j) && column)
		return (column + 4);//ra - sb
	if (column)
		return (column + 6);//rra - rb
	return (column + 2);
}

/* 8 5 12 -5 */
t_list	*ft_get_next_lesser()
{

}

int	ft_bubblesort(t_list *stack, int column)
{
	int	nbr_i;
	int	nbr_j;
	int	count;
	int	stack_len;

	nbr_i = (*(stack->content));
	nbr_j = (*(stack->next->content));
	stack_len = ft_lstsize(stack);
	if (nbr_i > nbr_j)
	{
		count = -1;
		while (++count < stack_len)
		{
		}
	}
}