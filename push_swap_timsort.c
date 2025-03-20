/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_timsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/20 15:26:57 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*	Returns the amount of runs that exist on a numeric T_LIST *.			*/
static int	ft_runcount(t_list *stack)
{
	int	run;
	int	count;

	run = -1;
	count = 0;
	while (stack)
	{
		if (stack->run != run)
		{
			run = stack->run;
			count++;
		}
		stack = stack->next;
	}
	return (count);
}

/*	Returns the most efficient run lenght to use during a quicksort			*/
/*	execution.																*/
static int	ft_getrlen(t_list **stacks)
{
	int	lstsize;
	int	rlen;

	rlen = 8;
	lstsize = ft_lstsize(stacks[0]) - 1;
	while ((lstsize % rlen != 0) && rlen < 16)
		rlen++;
	return (rlen);
}

/*	Solves which is the most efficient pair of runs to merge into STACK A	*/
/*	and executes mergesort to do so.										*/
/*	- It then repeats this process until the STACK B is empty.				*/
static void	ft_solve(t_list **stacks, char **order_lst, int runsize)
{
	t_pair	run;

	while (stacks[1])
	{
		if (ft_runcount(stacks[1]) <= (runsize / 2))
		{
			run.a = stacks[1]->run;
			if (runsize % 2 != 0)
			{
				run.b = run.a;
				runsize--;
			}
			else
				run.b = run.a - 1;
		}
		else
		{
			run.a = ft_lstlast(stacks[1])->run;
			run.b = run.a + 1;
		}
		if (ft_lstsize(stacks[1]) == ft_runsize(stacks[1], run.a))
			run.b = run.a;
		ft_mergesort(stacks, order_lst, &run);
	}
}

/*	Sorts a numeric T_LIST ** with an order efficiency of: O(n log (n))		*/
/*	- Being a hybrid algorithm, it executes a combination of the following:	*/
/*	|| Quicksort - To first split the stack as many times necessary.		*/
/*	|| Mergesort - To merge the runs previously divided by quicksort.		*/
/*	|| Insertionsort - Used by the previous to ensure the correct sorting.	*/
/*	NOTICE																	*/
/*	- If the list size is lesser than 64, quicksort will subdivide the list	*/
/*	  only in two runs. Bigger than the pivot and lesser, or equal, than 	*/
/*	  the pivot.															*/
void	ft_timsort(t_list **stacks, char **order_lst)
{
	int		lstsize;

	lstsize = ft_lstsize(stacks[0]);
	if (lstsize < 64)
		ft_quicksort(stacks, order_lst, 0);
	else
		ft_quicksort(stacks, order_lst, ft_getrlen(stacks));
	ft_solve(stacks, order_lst, ft_runcount(stacks[1]));
	while (ft_checksort_lst(stacks[0], -1))
		if (ft_execute(RRA_ORDER, stacks))
			ft_printf("%s\n", order_lst[RRA_ORDER]);
}
