/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_quicksort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/29 20:43:58 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Bubblesort arranges 2 and 3 numbers of one stack in the most efficient way.	*/

/* Selectionsort arranges 5 numbers from min to max or max to min. Using the	*/
/* minimum number or maximum number as reference, respectibly.					*/

/* Insertionsort finds the most efficient way to sort the frist number of a		*/
/* stack into the paralel one, in the most efficient way. (With a pivot respec)	*/
/* 	- This can be used for several porpuses, from sorting through an existing	*/
/*	  pivot, to separate numbers by digit relevance.							*/

/* Quicksort finds the middle pivot to separate 2 piles of numbers to sort, in	*/
/* the most efficient way. One of numbers lesser than the pivot, and one with	*/
/* numbers larger.																*/

/* Timsort skips arranged consecutive numbers. Combining it with Insertionsort	*/
/* to rearrange in the most eficient way.										*/

/* Radixsort, separates the numbers by its more relevant digit. Sorts them, then*/
/* follows with the next more relevant digit, sorts them. And so on until its	*/
/* all sorted.																	*/
/*	- This algorithm is the only one that has a "best case scenario". Recurring	*/
/*	  Insertionsort for each most non-relevant digit, and only aplying the one	*/
/*	  with lesser movements. As long as that group has 11 or less numbers, the	*/
/*	  remaining algorithms will always find the most effitient way to sort it.	*/
/*	- If a group of numbers has 12 or more numbers assigned to the same most	*/
/*	  non-relevant number. Special action is needed, but i haven't figured it	*/
/*	  out just yet.																*/


/* Step by step idea:															*/
/*	- Radixsort groups the numbers using it's most non-relevant digit as		*/
/*	  reference on the stack_a, and gives more attention to those groups with	*/
/*	  not more than 11 numbers. (what if it always choose a pivot for every 	*/
/*	  group, and we subdivded it as much as needed for Bubblesort or 			*/
/*	  Selectionsort to sort it in stack_b, then use Insertion sort to rearrange	*/
/*	  them into the "previous" pivot).											*/
/*	- Then Quicksort choose a pivot from that group, and in help with			*/
/*	  Insertionsort, finds the most efficient way to group every digit lower	*/
/*	  than the pivot into stack_b.												*/
/*	- While the numbers are being sent into the stack_b, Bubblesort and			*/
/*	  Selectinosort must be used to sort the arriving numbers. Since the group	*/
/*	  shouldn't be larger than 11, it each subgroup would have up to 5 numbers.	*/
/*	- Then Insertionsort rearanges them back into stack_a, all on top of the	*/
/*	  pivot, to finally repeat the proccess with the greater group of 5.		*/
/*	- Once the first group is sorted. Follows the next one.						*/
/*  - If this proccess is done correctly, the stack_a should be divided by		*/
/*	  groups of numbers (most non-relevant digit), and each one sorted as well.	*/
/*  - The next part is to repeat this proccess with the following most			*/
/*	  non-relevant digit.														*/

/*									   {P, S,       R, RR}						*/
/* Every order for stack_a is saved on {0 (pa), 2 (sa) , 4 (ra), 6 (rrb)} (even numbers).		*/
/* Every order for stack_b is saved on {1 (pb), 3 (rra), 5 (sb), 7 (rb) } (odd numbers).			*/
/* The formula being:														*/
/* Instruction index = column + (2 * pair).								*/
/* ____________________________________________________________				*/
/* | column | P (pair 0)| S (pair 2)| R (pair 4)| RR (pair 6) |				*/
/* |--------|-----------|-----------|-----------|-------------|				*/
/* | A = 0  | A + 0 = 0 | A + 2 = 2 | A + 4 = 4 |  A + 6 = 6  |				*/
/* | B = 1  | B + 0 = 1 | B + 2 = 3 | B + 4 = 5 |  B + 6 = 7  |				*/
/* |________|___________|___________|___________|_____________|				*/
/*																			*/

static	int	ft_inverse_getposition(int nbr, t_list *stack)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	count = 0;
	tmp = ft_lstlast(stack);
	stack_len = ft_lstsize(stack);
	while (stack && (nbr > (*(stack->content)) || nbr < (*(tmp->content))))
	{
		count++;
		tmp = stack;
		stack = stack->next;
	}
	if (!count)
		return (0);
	if (count > (stack_len / 2))
		return (-1);
	return (1);
}

static	int	ft_getposition(int nbr, t_list *stack, int column)
{
	t_list *tmp;
	int		count;
	int		stack_len;

	if (!stack)
		return (1);
	count = 0;
	tmp = ft_lstlast(stack);
	stack_len = ft_lstsize(stack);
	if (!column)
	{
		while (stack && (nbr > (*(stack->content)) || nbr < (*(tmp->content))))
		{
			count++;
			tmp = stack;
			stack = stack->next;
		}
	}
	else
		return (ft_inverse_getposition(nbr, stack));
	if (!count)
		return (0);
	if (count > (stack_len / 2))
		return (-1);
	return (1);
}

int	ft_insertionsort(t_list **stacks, int column)
{
	int	ans;

	if (!column)
	{
		ans = ft_getposition((*(stacks[0]->content)), stacks[1], 1);
		if (!ans || (!ft_check_sort(stacks[1], 1) && (*(stacks[0]->content)) > (*(stacks[1]->content))) || ft_lstsize(stacks[1]) <= 2)
			return (1);
		if (ans > 0)
			return (7);//rb
		return (6);//rrb
	}
	else
		ans = ft_getposition((*(stacks[1]->content)), stacks[0], 0);
	if (!ans)
		return (0);
	if (ans > 0)
		return (4);//ra
	return (3);//rra
}

/* Splits the stack with a middle pivot. */
int	ft_quicksort(t_list	**stacks, int column, int *pivot)
{
	if (!column)
	{
		if ((*(stacks[0]->content)) == (*pivot))
		{
			(*pivot) = ft_pvtchr(stacks[0], stacks[0]);	
			return (4);//ft_insertionsort();
		}
		if ((*(stacks[0]->content)) < (*pivot))
		{
			if (stacks[1])
				return (ft_insertionsort(stacks, column));//ft_insertionsort();
			return (1);
		}
		else
			return (4);
	}
	return (6);
}

/* Finds subsequences of sorted numbers and splits them in runs.			*/
/* Lets start with 32.														*/
/* Using quicksort to divide the pile, then insertion sort to create a run	*/
/* of 32 sorted numbers in stack_b.*/
/* int	ft_timsort() */

