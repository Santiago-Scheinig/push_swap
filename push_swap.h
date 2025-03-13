/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:55 by sscheini          #+#    #+#             */
/*   Updated: 2025/03/13 21:14:06 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
/*--------------------------------------------------------------------------*/
/*-------------------------------TROUBLESHOOT-------------------------------*/
/*--------------------------------------------------------------------------*/

# define ERR_END -1

/*	Frees a numeric T_LIST ** structure and the INT * array					*/
/*	used to create it.														*/
void	*ft_stack_free(int *ptr, t_list **stacks);							

/*	Frees a CHAR ** array generated by an ft_split execution.				*/
void	*ft_split_free(char **split);

/*	Verifies that the inputed values recieved as argument meet the			*/
/*	folowing requisites:													*/
/*	- Values inputed are integers numbers.									*/
/*	- Numbers inputed are betweeen the MAX_INT and MIN_INT, both included.	*/
/*	- Numbers inputed are unique and do not repeat.							*/
/*	If all the requisites are met returns an INT * array with the values.	*/
int		*ft_stack_check(char **argv, int *ptr_len);

/*	Push_swap failsafe.														*/
int		ft_forcend(int *ptr, t_list **stacks, char **order_arr);

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

/* Executes the instruction sent as argument one time with both stack_a		*/
/* and stack_b.																*/
/* - If executed correctly, returns 1. Else, returns 0.						*/
int		ft_double(int (*ins)(t_list **), t_list **stack_a, t_list **stack_b);

/* Executes a given instruction and prints it on stdout.					*/
/* - If the instruction isn't valid, returns -1.							*/
int		ft_execute(int instruction, t_list **stacks);

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

/*--------------------------------------------------------------------------*/
/*--------------------------------ALGORITHMS--------------------------------*/
/*--------------------------------------------------------------------------*/

void	ft_quicksort(t_list **stacks, char **order_lst, int rlen);

void	ft_mergesort(t_list **stacks, char **order_lst, int run_a, int run_b);

void	ft_timsort(t_list **stacks, char **order_lst);

/*	Sorts an individual stack of a numeric T_LIST ** with a					*/
/*	O(n) order solution.													*/
/*  - Use column to indicate which stack to sort. STACK A | 0 is sorted 	*/
/*	  minimum to maximum, STACK B | 1 is sorted maximum to minimum.			*/
/*	- For loop <= 3, the algorithm will execute 3 orders to sort the 		*/
/*	  indicated stack. If the amount of digits is less than 3, it will push */
/*	  an extra digit from the opossite stack.								*/
/*	- Use loop > 3 to indicate the amount of extra numbers to push from the	*/
/*	  opposite stack, and sort in the indicated one.						*/
/*	- Notice that for stacks of size > 3 sort is not guaranteed.			*/
void	ft_bubblesort(t_list **stacks, char **order_lst, int col, int dir);

int		ft_insertionsort(t_list *stack_des, int nbr, int run, int dir);

/*--------------------------------------------------------------------------*/
/*----------------------------------UTILITY---------------------------------*/
/*--------------------------------------------------------------------------*/

/*	Finds and returns the numeric T_LIST * structure with the limit number	*/
/*	of a run.																*/
/*	- Use positive direction for the maximum.								*/
/*	- Use negative direction for the minimum.								*/
/*	- Use run -1 to find the limit number of the whole stack instead.		*/
t_list	*ft_limitchr(t_list *stack, int run, int dir);

t_list	*ft_runchr(t_list *stack, int run, int *count);

t_list	*ft_nextnbr(t_list *stack, int *exe, int run);

int		ft_get_distance(t_list *stack, int nbr);

int		ft_runsort(t_list *stack, int run, int dir, int col);

int		ft_runsize(t_list *stack, int run);

int		ft_islimit(t_list *stack, int nbr, int dir, int run);

int		ft_translate(int order);

/*	Checks if a numeric T_LIST * structure is sorted.						*/
/*	- Positive direction checks max to min sort.							*/
/*	- Negative direction checks min to max sort.							*/
/*	- Returns the amount of sort errors found on the stack, 0 equals sorted.*/
/*	- Notice that an empty list is a sorted one.							*/
int		ft_checksort_lst(t_list *stack, int col);





/////

void	ft_print_stack(t_list **stack);

void	ft_printruns(t_list	*stack);

#endif