/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/30 21:14:25 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//to solve, still issue with pivot.
static void	ft_merge(t_list **stacks, char **lst_instructions)
{
	int	order;
	int	loop;

	loop = 0;
	//ft_printf("MERGE\n");
	while (stacks[1] && loop++ < 20)
	{
		if ((*(stacks[0]->content)) > (*(stacks[1]->content)) && !ft_check_sort(stacks[0], -1)) 
			order = 0;
		else
			order = ft_insertionsort(stacks, stacks[0]->content, 1);
		if (order < 0)
			order = 0;
		if (ft_execute(lst_instructions[order], stacks))
			ft_printf("%s\n", lst_instructions[order]);
	}
	while (ft_check_sort(stacks[0], -1) && loop++ < 22)
	{
		//ft_print_stack(stacks);
		if (ft_execute(lst_instructions[3], stacks))
			ft_printf("%s\n", lst_instructions[3]);
	}
}

//clean
static void	ft_orders(t_list **stacks, int *order_a, int *order_b, int *pivot)
{
	int	stack_len;

	*(order_a) = -1;
	if (ft_check_sort(stacks[0], -1))
	{
		stack_len = ft_lstsize(stacks[0]); 
		if (2 <= stack_len && stack_len <= 3)
			*(order_a) = ft_bubblesort(stacks[0], -1);
		else
			*(order_a) = ft_quicksort(stacks, pivot, 0);
	}
	*(order_b) = -1;
	stack_len = ft_lstsize(stacks[1]);
	if (ft_check_sort(stacks[1], 1))
		if (2 <= stack_len && stack_len <= 3 && *(order_a) != 1)
			*(order_b) = ft_bubblesort(stacks[1], 1);
	*(order_b) = ft_quicksort(stacks, pivot, 1);
	if (*(order_b) > -1 && *(order_a) == 1)
		*(order_a) = -1;
	if (*(order_b) == -1 && ft_check_sort(stacks[1], 1))
		*(order_b) = ft_islimit(stacks[1], ft_getmin_nbr(stacks[1]), 1);
}

//clean
static void	ft_solve(t_list **stacks, char	**lst_instructions)
{
	int	pivot;
	int	order_a;
	int	order_b;
	//int	loop;//-

	//loop = 0;//-
	pivot = ft_pvtchr(stacks[0], stacks[0]);
	while ((((ft_check_sort(stacks[0], -1)) || ft_check_sort(stacks[1], 1)))) //&& loop++ < 30)//-
	{
		//ft_print_stack(stacks);//-
		ft_orders(stacks, &order_a, &order_b, &pivot);
		if (order_a == order_b - 3)
		{
			if (ft_execute(lst_instructions[order_b + 3], stacks))
				ft_printf("%s\n", lst_instructions[order_b + 3]);
			continue ;
		}
		if (order_a != -1)
			if (ft_execute(lst_instructions[order_a], stacks))
				ft_printf("%s\n", lst_instructions[order_a]);
		if (order_b != -1)
			if (ft_execute(lst_instructions[order_b], stacks))
				ft_printf("%s\n", lst_instructions[order_b]);
	}
	ft_merge(stacks, lst_instructions);
}

/* Verifies the proper format of the inputed values; If values are valid,	*/
/* it initializes the stack of numbers as T_LIST ** array. 					*/
/* - Returns NULL in case of error or non valid values.						*/
static	t_list	**ft_stack_ini(char **argv, int **ptr)
{
	t_list	**stack;
	t_list	*aux;
	int		ptr_len;
	int		i;
	
	(*ptr) = ft_stack_check(argv, &ptr_len);
	if (!(*ptr))
		return (NULL);
	stack = (t_list **) malloc(2 * sizeof(t_list *));
	if (!stack)
		return (NULL);
	stack[0] = NULL;
	stack[1] = NULL;
	i = 0;
	while (++i < ptr_len + 1)
	{
		aux = ft_lstnew(&(*ptr)[i - 1]);
		if (!aux)
			return (NULL);
		ft_lstadd_back(&stack[0], aux);
	}
	return (stack);
}

/* Push_swap is a program dedicated to sort an array of integers numbers	*/
/* without duplicates, using only two stacks and limited movement 			*/
/* instructions, giving a O(n^2) deterministic solution.					*/
int	main(int argc, char **argv) 
{
	t_list	**stacks;
	char	**lst_instructions;
	int		*ptr;

	if (argc < 2)
		return (0);
	stacks = ft_stack_ini(argv, &ptr);
	lst_instructions = ft_split("pa pb sa rra ra sb rrb rb ss rrr rr", ' ');
	if (!stacks || !lst_instructions)
		return (ft_forcend(ptr, stacks, lst_instructions));
	ft_solve(stacks, lst_instructions);
	//ft_print_stack(stacks);//-
	ft_stack_free(ptr, stacks);
	ft_split_free(lst_instructions);
	return (0);
}
