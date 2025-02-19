/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_timsort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:33:54 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/19 21:25:02 by sscheini         ###   ########.fr       */
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

/* Splits the stack with a middle pivot. */

/* Finds subsequences of sorted numbers and splits them in runs.			*/
/* Lets start with 32.														*/
/* Using quicksort to divide the pile, then insertion sort to create a run	*/
/* of 32 sorted numbers in stack_b.*/
/* int	ft_timsort() */

void	ft_printruns(t_list	*stack)
{
	while (stack)
	{
		ft_printf("NBR |%i| - RUN |%i|\n", *(stack->content), stack->run);
		stack = stack->next;
	}		
}

int	ft_main_runchr(t_list *stack, int max_run)
{
	int	run;
	int	aux_runsize;
	int	main_run;
	int	main_runsize;
	
	run = -2;
	main_run = max_run;
	main_runsize = 0;
	while (++run <= max_run)
	{
		aux_runsize = ft_runsize(stack, run);
		if (aux_runsize >= main_runsize)
		{
			main_runsize = aux_runsize;
			main_run = run;
		}
		run++;
	}
	//ft_printf("MAIN RUN |%i| - SIZE |%i|\n", main_run, main_runsize);
	return (main_run);
}



int	ft_runmod(t_list *stack, int run, int new_run)
{
	while (stack)
	{
		if (stack->run == run)
		{
			while (stack && stack->run == run)
			{
				stack->run = new_run;
				stack = stack->next;
			}
			return (1);
		}
		stack = stack->next;
	}
	return (0);
}

int	ft_limit_runchr(t_list *stack, int run, int limit)
{
	while (stack)
	{
		if (stack->next && stack->run == run)
		{
			if (limit < 0)
				return (*(stack->content));
			while (stack->next && stack->next->run == run)
				stack = stack->next;
			return (*(stack->content));
		}
		stack = stack->next;
	}
	return (-1);
}

void	ft_splited_runchr(t_list *stack, int max_run)
{
	int	i;
	int	run;
	int	limit_run;

	run = -1;
	while (++run <= max_run)
	{
		i = run;
		limit_run = ft_limit_runchr(stack, run, 1);
		while (++i <= max_run)
		{
			if (limit_run != -1 && limit_run < ft_limit_runchr(stack, i, -1))
			{
				ft_runmod(stack, i, run);
				break ;
			}
		}
	}
}

int		ft_get_minrun(t_list *stack)
{
	int	ans;
	int	min_run;
	int	stack_len;

	min_run = 16;
	stack_len = ft_lstsize(stack);
	ans = stack_len / min_run;
	while ((ans % 2) != 0 && min_run != 8)
		ans = stack_len / --min_run;
	return (min_run);
}

/* void	ft_merge_norun(t_list **stacks, char **order_lst, int run)
{
	if (stacks[0]->next->run == -1)
	{
		while (stacks[0]->run == -1)
		{
			if (ft_execute(PB_ORDER, stacks))
				ft_printf("%s\n", order_lst[PB_ORDER]);
			if (ft_execute(RB_ORDER, stacks))
				ft_printf("%s\n", order_lst[RB_ORDER]);
		}
	}
	if (ft_execute(ft_bubblesort(stacks, order_lst, -1), stacks))
	{
		stacks[0]->run == run;
		stacks[0]->next->run == run;
		ft_printf("%s\n", order_lst[SA_ORDER]);
	}
}*/

int	ft_sort_run(t_list *stack, int run, int dir)
{
	int	count;
	int	limit;
	int	order;

	count = 0;
	order = RA_ORDER;
	limit = *(ft_limitchr(stack, run, dir)->content);
	while (stack && stack->run == run)
	{
		if (*(stack->content) == limit)
			break ;
		count++;
		stack = stack->next;
	}
	if (!count)
		return (NO_ORDER);
	if (count > ft_lstsize(stack))
		order = RRA_ORDER;
	if (dir >= 0)
		order += 3;
	return (order);
}
void	ft_make_minrun(t_list **stacks, char **order_lst, int min_run)
{
	int	order;
	int	run_size;

	run_size = ft_runsize(stacks[1], 0);
	while (run_size < min_run)
	{
		ft_print_stack(stacks);
		order = ft_insertionsort(stacks[1], *(stacks[0]->content), 0, 1);
		ft_printf("ORDER |%s|", order_lst[order]);
		if (ft_execute(order, stacks))
		{
			ft_printf("%s\n", order_lst[order]);
			if (order == PB_ORDER)
			{
				stacks[1]->run = 0;
				run_size++;
			}
		}
	}
}

/* 	while (ft_runsize(stacks[1], -1) < min_run)
	{
		//ft_print_stack(stacks);
		if (main_run && stacks[0]->run == main_run)
			order = RA_ORDER;
		if (stacks[0] && stacks[0]->run != main_run)
			order = ft_insertionsort(stacks[1], *(stacks[0]->content), -1, 1, 1);
		if (!ft_checksort_run(stacks[1], 1, -1) && stacks[0]->run != main_run)
			if (*(stacks[0]->content) > *(stacks[1]->content) 
				|| *(stacks[0]->content) < *(ft_lstlast(stacks[1])->content))
				order = PB_ORDER;
		if (order == NO_ORDER)
			order = PB_ORDER;
		if (order != NO_ORDER && ft_execute(order, stacks))
		{
			ft_printf("%s\n", order_lst[order]);
			if (order == PB_ORDER)
				stacks[1]->run = -1;
		}
	} */
/* 	while (ft_checksort_run(stacks[1], 1, -1))
		if (ft_execute(ft_insertionsort(stacks[1], ft_lstlimit_chr(stacks[1], 1, -1), -1, 1, 1)))
			ft_printf("%s\n",) */

void	ft_solve(t_list **stacks, char **order_lst, int main_run, int min_run)
{
	//int	stack_len;
	int order;
	int	loop;
	int	second_loop;

	loop = 0;
	second_loop = 0;
	if (main_run != -1)
		main_run = -1;
	if (min_run)
		min_run = 8;
	while (loop++ < 2)
	{
		if (ft_execute(PB_ORDER, stacks))
			ft_printf("%s\n", order_lst[PB_ORDER]);
		stacks[1]->run = 0;
		if (ft_execute(PB_ORDER, stacks))
			ft_printf("%s\n", order_lst[PB_ORDER]);
		stacks[1]->run = 0;
		if (*(stacks[1]->content) < *(stacks[1]->next->content))
			if (ft_execute(SB_ORDER, stacks))
				ft_printf("%s\n", order_lst[SB_ORDER]);
		ft_make_minrun(stacks, order_lst, min_run);
		while (ft_checksort_run(stacks[1], 1, 0) && ++second_loop < 5)
		{
			ft_printruns(stacks[1]);//-
			order = ft_sort_run(stacks[1], 0, 1);
			if (ft_execute(order, stacks))
				ft_printf("%s\n", order_lst[order]);	
		}
		ft_setruns(stacks[1], 1, 1);
		ft_printruns(stacks[1]);//-
		ft_print_stack(stacks);//-
	}
}
// if a number is part of a negative run there's two possible ways to exploit it.
// if the next number isn't part of a negative run, saving the number in the back
// while we push the positive run, until we find its right position and push it with it.
// if there exists more than 1 number part of a negative run, PB + RRB will sort them in
// ascending way as we push them. Creating a new sorted run.		
void	ft_timsort(t_list **stacks, char **order_lst)
{
	int	end_run;
	int	main_run;
	int	min_run;
	//int	run_size;
	//int	run_size_prev;

	min_run = ft_get_minrun(stacks[0]);
	end_run = ft_setruns(stacks[0], 0, -1);
	ft_splited_runchr(stacks[0], end_run);
	main_run = ft_main_runchr(stacks[0], end_run);
	//ft_printruns(stacks[0]);
	if (ft_runsize(stacks[0], main_run) >= min_run)
		ft_solve(stacks, order_lst, main_run, min_run);
	else
		ft_solve(stacks, order_lst, 0, min_run);
/* 	run_size = ft_runsize(stacks[0], run);
	run_size_prev = 0;
	while (stacks[0])
	{
		if (run_size > 0)
		{
			if (run_size == run_size_prev || run_size == run_size_prev -1)
			{
				ft_merge(stacks, order_lst, run);
				break;
			}
			else
				ft_passrun(stacks, order_lst, run);
		}
		run_size_prev = run_size;
		run_size = ft_runsize(stacks[0], ++run);
	} */
}
