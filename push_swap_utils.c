/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:54:56 by sscheini          #+#    #+#             */
/*   Updated: 2025/02/20 20:51:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_prints(t_list **stack)
{
	t_list	*aux;
	int		*ptr;
	int		ans;

	if (!stack)
		return ;
	ans = 0;
	aux = (*stack);
	while (aux)
	{
		ptr = aux->content;
		ans += ft_printf("| %-03i |\n", *ptr);
		aux = aux->next;
	}
}

void	ft_print_stack(t_list **stacks)
{
	if (!stacks)
		return ;
	ft_printf("A.\n");
	ft_prints(&stacks[0]);
	ft_printf("B.\n");
	ft_prints(&stacks[1]);
}

/*	Finds and returns the next numeric T_LIST * structure, with a 			*/
/*	lesser or higher value than nbr.										*/
/*	- Use a positive orientation for higher numbers.						*/
/*	- Use a negative orientation for lesser numbers.						*/
/*	- Returns NULL if no valid number was found.							*/
t_list	*ft_nextnbr_chr(t_list *stack, int nbr, int dir)
{
	while (stack)
	{
		if (dir < 0)
			if (*(stack[0].content) < nbr)
				return (stack);
		if (dir >= 0)
			if (*(stack[0].content) > nbr)
					return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/*	Checks if a numeric T_LIST * structure is sorted.						*/
/*	- Positive direction checks max to min sort.							*/
/*	- Negative direction checks min to max sort.							*/
/*	- Returns the amount of sort errors found on the stack, 0 equals sorted.*/
/*	- Notice that an empty list is a sorted one.							*/
int	ft_checksort_lst(t_list *stack, int col)
{
	int	nbr_i;
	int	nbr_j;
	int	ans;
	
	ans = 0;
	if (!stack || ft_lstsize(stack) <= 1)
		return (ans);
	while (stack)
	{
		nbr_i = *(stack->content);
		if (stack->next)
			nbr_j = *(stack->next->content);
		if (!col && nbr_i > nbr_j)
			ans++;
		if (col && nbr_i < nbr_j)
			ans++;
		stack = stack->next;
	}
	return (ans);
}

/*	Executes a given instruction.											*/
/*	- If the instruction isn't valid, returns 0.							*/
int	ft_execute(int instruction, t_list **stacks)
{
	if (instruction == SA_ORDER)
		return (ft_swap(&stacks[0]));
	else if (instruction == SB_ORDER)
		return (ft_swap(&stacks[1]));
	else if (instruction == SS_ORDER)
		return (ft_double_ins(ft_swap, &stacks[0], &stacks[1]));
	else if (instruction == PA_ORDER)
		return (ft_push(&stacks[1], &stacks[0]));
	else if (instruction == PB_ORDER)
		return (ft_push(&stacks[0], &stacks[1]));
	else if (instruction == RA_ORDER)
		return (ft_rotate(&stacks[0]));
	else if (instruction == RB_ORDER)
		return (ft_rotate(&stacks[1]));
	else if (instruction == RR_ORDER)
		return (ft_double_ins(ft_rotate, &stacks[0], &stacks[1]));
	else if (instruction == RRA_ORDER)
		return (ft_reverse_rotate(&stacks[0]));
	else if (instruction == RRB_ORDER)
		return (ft_reverse_rotate(&stacks[1]));
	else if (instruction == RRR_ORDER)
		return (ft_double_ins(ft_reverse_rotate, &stacks[0], &stacks[1]));
	return (0);
}

int	ft_get_distance(t_list *stack, int nbr, int dir)
{
	int	count;

	count = 0;
	if (dir < 0)
		count = ft_lstsize(stack);
	while (*(stack->content) != nbr)
	{
		if (dir < 0)
			count--;
		else
			count++;
		stack = stack->next;
	}
	return (count);
}