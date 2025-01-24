/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:37:04 by sscheini          #+#    #+#             */
/*   Updated: 2025/01/24 16:15:29 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	int	ft_solve_stack(t_list *stack, int column)
{
	int	stack_len;
	int	order;
	
	order = 0;
	stack_len = ft_lstsize(stack);
	if (!stack_len)
		return (0);
	if (1 < stack_len && stack_len <= 3)
		order = ft_bubblesort(stack, column);
	if (3 < stack_len && stack_len <= 7)
		order = ft_quicksort(stack, column);
	/*if (lst_size > 5)
		ft_raditzsort();*/
	return (order);
}

static	void	ft_solve(t_list **stacks, char	**lst_instructions)
{
	int	pivot;
	int	order_a;
	int	order_b;

	pivot = ft_pvtchr(stack[0], ft_get_maxint(stack[0]));
	while (!ft_check_sort(stacks[0]) || !ft_check_sort(stacks[1]))
	{
		order_a = ft_solve_stack(stacks[0], 0);
		order_b = ft_solve_stack(stacks[1], 1);
		if (order_a == order_b - 3)
			ft_execute(lst_instructions[order_b + 3], stacks);
		else
		{
			if (order_a != 0)
				if (ft_execute(lst_instructions[order_a], stacks))
					ft_printf("%s\n", lst_instructions[order_a]);
			if (order_b != 0)
				if (ft_execute(lst_instructions[order_b], stacks))
					ft_printf("%s\n", lst_instructions[order_b]);
/* 			else if (ft_insertionsort(stacks) > 0)
				ft_execute(lst_instructions[6]);
			else if (ft_insertionsort(stacks) < 0)
				ft_execute(lst_instructions[7]);*/
		}
	}
	while (stacks[1])
		if (ft_execute(lst_instructions[0], stacks))
			ft_printf("%s\n", lst_instructions[0]);	
}

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
	ft_print_stack(stacks);
	ft_solve(stacks, lst_instructions);
	ft_print_stack(stacks);
	ft_stack_free(ptr, stacks);
	ft_split_free(lst_instructions);
	return (0);
}
