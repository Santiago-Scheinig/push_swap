/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/29 20:41:54 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_merge_stacks(t_list **stacks, char **lst_instructions)
{
	int	order;
	int	loop;

	loop = 0;
	ft_printf("\nMERGE\n");
	while (stacks[1] && loop++ < 20)
	{
		//ft_print_stack(stacks);
		if ((*(stacks[0]->content)) > (*(stacks[1]->content)) && !ft_check_sort(stacks[0], 0)) 
			order = 0;
		else
			order = ft_insertionsort(stacks, 1);
		if (ft_execute(lst_instructions[order], stacks))
			ft_printf("%s\n", lst_instructions[order]);
	}
	while (ft_check_sort(stacks[0], 0) && loop++ < 22)
	{
		//ft_print_stack(stacks);
		if (ft_execute(lst_instructions[3], stacks))
			ft_printf("%s\n", lst_instructions[3]);
	}
}

static	int	ft_solve_stack(t_list **stacks, int column, int *pivot)
{
	int	stack_len;
	int	order;
	
	order = -1;
	stack_len = ft_lstsize(stacks[column]);
	if (!stack_len || !ft_check_sort(stacks[column], column))
		return (-1);
	if (1 < stack_len && stack_len <= 3)
		order = ft_bubblesort(stacks[column], column);
	else //if (3 < stack_len && stack_len <= 7)
		order = ft_quicksort(stacks, column, pivot);
	/*else
		ft_timsort();*/
	return (order);
}

static	void	ft_solve(t_list **stacks, char	**lst_instructions)
{
	int	pivot;
	int	order_a;
	int	order_b;
	//int	loop;

	//loop = 0;
	pivot = ft_pvtchr(stacks[0], stacks[0]);
	while (((ft_check_sort(stacks[0], 0) || ft_check_sort(stacks[1], 1))))
	{
		//ft_print_stack(stacks);
		order_a = ft_solve_stack(stacks, 0, &pivot);
		order_b = ft_solve_stack(stacks, 1, &pivot);
		if (order_a == order_b - 3)
		{
			ft_execute(lst_instructions[order_b + 3], stacks);
			ft_printf("%s\n", lst_instructions[order_b + 3]);
		}
		else
		{
			if (order_a >= 0)
				if (ft_execute(lst_instructions[order_a], stacks))
					ft_printf("%s\n", lst_instructions[order_a]);
			if (order_b >= 0 && ft_lstsize(stacks[1]) > 3)
				if (ft_execute(lst_instructions[order_b], stacks))
					ft_printf("%s\n", lst_instructions[order_b]);
		}
	}
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
	ft_merge_stacks(stacks, lst_instructions);
	//ft_print_stack(stacks);
	ft_stack_free(ptr, stacks);
	ft_split_free(lst_instructions);
	return (0);
}
