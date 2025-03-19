/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:55 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/17 18:04:07 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
/*--------------------------------------------------------------------------*/
/*-------------------------------TROUBLESHOOT-------------------------------*/
/*--------------------------------------------------------------------------*/

/*	Verifies that the inputed values recieved as argument meet the			*/
/*	folowing requisites:													*/
/*	- Values inputed are integers numbers.									*/
/*	- Numbers inputed are betweeen the MAX_INT and MIN_INT, both included.	*/
/*	- Numbers inputed are unique and do not repeat.							*/
/*	If all the requisites are met returns an INT * array with the values.	*/
int		*ft_stack_check(char **argv, int *ptr_len);

/*	Frees a numeric T_LIST ** structure and the INT * array					*/
/*	used to create it.														*/
void	*ft_stack_free(int *ptr, t_list **stacks);							

/*	Frees a CHAR ** array generated by an ft_split execution.				*/
void	*ft_split_free(char **split);

/*	Push_swap failsafe.														*/
int		ft_forcend(int *ptr, t_list **stacks, char **order_lst);

/*--------------------------------------------------------------------------*/
/*-------------------------------INSTRUCTIONS-------------------------------*/
/*--------------------------------------------------------------------------*/

# define NO_ORDER -1

/* Pushes the first element from STACK B to STACK A as it's first.			*/
# define PA_ORDER 0

/* Pushes the first element from STACK A to STACK B as it's first.			*/
# define PB_ORDER 1

/* Swaps the first two elements of STACK A.									*/
# define SA_ORDER 2

/* Rotates every element on STACK A one position down, making the last		*/
/* element it's first.														*/
# define RRA_ORDER 3

/* Rotates every element on STACK A one position up, making the first		*/
/* element it's last.														*/
# define RA_ORDER 4

/* Swaps the first two elements of STACK B.									*/
# define SB_ORDER 5

/* Rotates every element on STACK B one position down, making the last		*/
/* element it's first.														*/
# define RRB_ORDER 6

/* Rotates every element on STACK B one position up, making the first		*/
/* element it's last.														*/
# define RB_ORDER 7

/* Swaps the first two elements of both STACKS.								*/
# define SS_ORDER 8

/* Rotates every element on both STACKS one position down, making the last	*/
/* elements their first.													*/
# define RRR_ORDER 9

/* Rotates every element on both STACKS one position up, making the first	*/
/* elements their last.														*/
# define RR_ORDER 10

/* Pushes the first element from stack_src to stack_des as it's first.		*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_push(t_list **stack_src, t_list **stack_des);

/* Rotates every element on the stack one position down, making the last	*/
/* element it's first.														*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_reverse_rotate(t_list **stack);

/* Rotates every element on the stack one position up, making the first		*/
/* element it's last.														*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_rotate(t_list **stack);

/* Swaps the first two elements of the stack passed as argument.			*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_swap(t_list **stack);

/* Executes the instruction sent as argument one time with both stack_a		*/
/* and stack_b.																*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_double(int (*ins)(t_list **), t_list **stack_a, t_list **stack_b);

/*	Executes a given instruction:											*/
/*	||	PA_ORDER	==	0													*/
/*	||	PB_ORDER	==	1													*/
/*	||	SA_ORDER	==	2													*/
/*	||	RA_ORDER	==	3													*/
/*	||	RRA_ORDER	==	4													*/
/*	||	SB_ORDER	==	5													*/
/*	||	RB_ORDER	==	6													*/
/*	||	RRB_ORDER	==	7													*/
/*	||	SS_ORDER	==	8													*/
/*	||	RR_ORDER	==	9													*/
/*	||	RRR_ORDER 	==	10													*/
/*	- If the instruction isn't valid, returns 0.							*/
int		ft_execute(int instruction, t_list **stacks);

typedef struct s_pair
{
	int				a;
	int				b;
}	t_pair;

/*--------------------------------------------------------------------------*/
/*--------------------------------ALGORITHMS--------------------------------*/
/*--------------------------------------------------------------------------*/

/*	Sorts a stack of a numeric T_LIST ** with an order solution efficiency	*/
/*	of: O(n^2) to O(n log (n)).												*/
/*	- To sort the stack it will split it with a middle pivot and push every	*/
/*	  number bigger than the pivot to the second stack, using Insertionsort	*/
/*	  to verify the correct sorting. Then, it will repeat the same process	*/
/*	  with the numbers lesser than the pivot.								*/
/*	- Use rlen != 0 to subdivide the numbers sorted with Insertionsort into */
/*	  runs of the decleared size.											*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- If rlen is define, quicksort doesn't sort the totallity of the stack, */
/*	  but the subdivided runs.												*/
/*	- Additionally, once the first round of bigger numbers is pushed to the	*/
/*	  second stack, it will find the pivot of the remaining numbers, and	*/
/*	  push the lesser numbers this time, repeating this last process until	*/
/*	  only one number is left.												*/
void	ft_quicksort(t_list **stacks, char **order_lst, int rlen);

/*	Merges and sorts a numeric T_LIST ** using the runs sent as argument 	*/
/*	with an order efficiency of: O(n log(n)).								*/
/*	- Use run.a to declare the first run to merge. This should be the run	*/
/*	  at the beggining or end of the stack.									*/
/*	- Use run.b to declare the second run to merge. This should be the run	*/
/*	  next the first run (the following or previous run respectibly).		*/
/*	- Use run.a == run.b to merge a single run.								*/
/*	NOTICE																	*/
/*	|-|																		*/
/*	- Mergesort can only sort numeric T_LIST ** with rollercoaster format.	*/
void	ft_mergesort(t_list **stacks, char **order_lst, t_pair *run);

/*	Sorts a numeric T_LIST ** with an order efficiency of: O(n log (n))		*/
/*	- Being a hybrid algorithm, it executes a combination of the following:	*/
/*	|| Quicksort - To first split the stack as many times necessary.		*/
/*	|| Mergesort - To merge the runs previously divided by quicksort.		*/
/*	|| Insertionsort - Used by the previous to ensure the correct sorting.	*/
/*	NOTICE																	*/
/*	- If the list size is lesser than 64, quicksort will subdivide the list	*/
/*	  only in two runs. Bigger than the pivot and lesser, or equal, than 	*/
/*	  the pivot.															*/
void	ft_timsort(t_list **stacks, char **order_lst);

/*	Executes up to three instructions to sort an individual stack of a		*/
/*	numeric T_LIST ** with an order efficiency of: O(n).					*/
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
void	ft_bubblesort(t_list **stacks, char **order_lst, int col, int dir);

/*	Returns the order needed to sort the nbr sent as argument into it's		*/
/*	correct position in the destination stack, with an order efficiency of:	*/
/*	O(n^2).																	*/
/*	- Use positive direction to sort from maximum to minimum.				*/
/*	- Use negative direction to sort from minimum to maximum.				*/
/*	- If run is defined, it will return the order needed to sort nbr into	*/
/*	  it's correct position within the run in the destination stack.		*/
int		ft_insertionsort(t_list *stack_des, int nbr, int run, int dir);

/*--------------------------------------------------------------------------*/
/*----------------------------------UTILITY---------------------------------*/
/*--------------------------------------------------------------------------*/

/*	Returns the position in the stack with the first number that is part of	*/
/*	the indicated run.														*/
/*	- Additionally, increases count for each position in the stack passed.	*/
/*	- Returns NULL if no number with the indicated run is find.				*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- Count is increased even if NULL is returned.							*/
t_list	*ft_runchr(t_list *stack, int run, int *count);

/*	Finds and returns the numeric T_LIST * structure with the limit number	*/
/*	of a run.																*/
/*	- Use positive direction for the maximum.								*/
/*	- Use negative direction for the minimum.								*/
/*	- Use run -1 to find the limit number of the whole stack instead.		*/
t_list	*ft_limitchr(t_list *stack, int run, int dir);

/*	Returns the position on the stack of the next closest number with		*/
/*	the indicated run.														*/
/*	- Additionally, it saves the instruction needed to place it in the		*/
/*	  first position, into exe.												*/
t_list	*ft_nextnbr(t_list *stack, int *exe, int run);

/*	Returns the amount of numbers in the stack with the indicated run.		*/
int		ft_runsize(t_list *stack, int run);

/*	Returns the most efficient instruction to get the indicated run limit 	*/
/*	in first position.														*/
/*	- Use negative direction to use the minimum limit as reference.			*/
/*	- Use positive direction to use the maximum limit as reference.			*/
/*	NOTICE 																	*/
/*	|-|																		*/
/*	- If the indicated run limit is in first position, returns NO_ORDER.	*/
int		ft_runsort(t_list *stack, int run, int dir);

/*	Returns the distance from the first position of the stack and the		*/
/*	indicated number.														*/
/*	- If the number isn't found, it returns the size of the stack.			*/
int		ft_get_distance(t_list *stack, int nbr);

/*	Translates the order sent as argument into its paralel version, and		*/
/*	returns it.																*/
/*	- Any order that would be executed in the STACK A is translated to 		*/
/*	  execute in the STACK B, and viceversa.								*/
int		ft_translate(int order);

/*	Checks if a numeric T_LIST * structure is sorted.						*/
/*	- Positive direction checks max to min sort.							*/
/*	- Negative direction checks min to max sort.							*/
/*	- Returns the amount of sort errors found on the stack, 0 equals sorted.*/
/*	- Notice that an empty list is a sorted one.							*/
int		ft_checksort_lst(t_list *stack, int dir);

#endif